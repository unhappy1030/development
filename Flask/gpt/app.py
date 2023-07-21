from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_restful import Resource, Api
import os


BASE_DIR = os.path.dirname(__file__)

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///{}'.format(os.path.join(BASE_DIR, 'test.db'))
db = SQLAlchemy(app)
api = Api(app)

class User(db.Model):
  id = db.Column(db.Integer, primary_key=True)
  username = db.Column(db.String(80), unique=True, nullable=False)
  email = db.Column(db.String(120), unique=True, nullable=False)
  
  def __repr__(self):
    return f'<User {self.username}>'

class UserResource(Resource):
  def get(self, user_id):
    user = User.query.get(user_id)
    if user is None:
      return {"error": "user not found"}, 404
    return {"username":user.username, "email" : user.email}

api.add_resource(UserResource, '/user/<int:user_id>')

if __name__ == '__main__':
  with app.app_context():
    db.create_all()
  app.run(debug=True)