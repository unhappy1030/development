from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy
from flask_restful import Resource, Api
from werkzeug.security import generate_password_hash, check_password_hash
from email_validator import validate_email, EmailNotValidError
from google.cloud import language_v1
import os
from google.oauth2 import service_account

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "C:/Users/white/Desktop/development/Flask/gpt/igneous-impulse-393612-3abe2a7a7275.json"

def analyze_text_sentiment(text):
    client = language_v1.LanguageServiceClient()

    document = language_v1.Document(content=text, type_=language_v1.Document.Type.PLAIN_TEXT)

    sentiment = client.analyze_sentiment(document=document).document_sentiment

    return sentiment.score, sentiment.magnitude
BASE_DIR = os.path.dirname(__file__)

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///{}'.format(os.path.join(BASE_DIR, 'test.db'))
db = SQLAlchemy(app)
api = Api(app)

class User(db.Model):
  id = db.Column(db.Integer, primary_key=True)
  username = db.Column(db.String(80), unique=True, nullable=False)
  password_hash = db.Column(db.String(128))
  email = db.Column(db.String(120), unique=True, nullable=False)
  
  def __repr__(self):
    return f'<User {self.username}>'

class UserResource(Resource):
  def get(self, user_id):
    user = User.query.get(user_id)
    if user is None:
      return {"error": "user not found"}, 404
    return {"username": user.username, "email" : user.email}
  def post(self):
    username = request.json.get('username')
    password = request.json.get('password')
    email = request.json.get('email')
    
    if password is None:
      return {"error": "Password is required"}, 400

    if len(username) < 5 or len(username) > 20:
        return {"error": "username must be between 5 and 20 characters"}, 400
    
    try:
        v = validate_email(email)
        email = v["email"]
    except EmailNotValidError as e:
        return {"error": str(e)}, 400

    # Add this code to validate the password
    if len(password) < 8 or len(password) > 15:
        return {"error": "Password must be 8 to 15 characters long"}, 400

    password_hash = generate_password_hash(password)
    
    user = User(username=username, email=email, password_hash=password_hash)
    db.session.add(user)
    db.session.commit()
    return {"message": "user created", "user_id": user.id}, 201

api.add_resource(UserResource, '/user/<int:user_id>', '/user')

class UserListResource(Resource):
    def get(self):
        users = User.query.all()
        return [{"user_id":user.id,"username": user.username, "email": user.email} for user in users]

api.add_resource(UserListResource, '/users')

class UserLoginResource(Resource):
    def post(self):
        username = request.json.get('username')
        password = request.json.get('password')
        
        user = User.query.filter_by(username=username).first()

        if user and check_password_hash(user.password_hash, password):
            return {"message": "Login successful", "user_id": user.id}, 200
        else:
            return {"message": "Username or password incorrect"}, 401

api.add_resource(UserLoginResource, '/login')

class Analysis(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    text = db.Column(db.String(500), nullable=False)
    score = db.Column(db.Float, nullable=False)
    magnitude = db.Column(db.Float, nullable=False)

class AnalysisResource(Resource):
    def get(self, analysis_id):
        analysis = Analysis.query.get(analysis_id)
        if analysis is None:
            return {"error": "Analysis not found"}, 404
        return {"text": analysis.text, "score": analysis.score, "magnitude": analysis.magnitude}

    def post(self):
        text = request.json.get('text')
        
        if text is None:
            return {"error": "Text is required for sentiment analysis"}, 400

        client = language_v1.LanguageServiceClient()

        document = language_v1.Document(content=text, type_=language_v1.Document.Type.PLAIN_TEXT)

        sentiment = client.analyze_sentiment(request={'document': document}).document_sentiment

        analysis = Analysis(text=text, score=sentiment.score, magnitude=sentiment.magnitude)
        db.session.add(analysis)
        db.session.commit()

        return {
            "message": "Analysis created",
            "analysis_id": analysis.id,
            'score': sentiment.score,
            'magnitude': sentiment.magnitude,
        }, 201

api.add_resource(AnalysisResource, '/analysis/<int:analysis_id>', '/analysis')

class AnalysisListResource(Resource):
    def get(self):
        analyses = Analysis.query.all()
        return [{"analysis_id": analysis.id, "text": analysis.text, "score": analysis.score, "magnitude": analysis.magnitude} for analysis in analyses]

api.add_resource(AnalysisListResource, '/analyses')



if __name__ == '__main__':
  with app.app_context():
    db.create_all()
  app.run(debug=True)
