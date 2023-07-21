from flask import Flask, request, jsonify, make_response
from flask_sqlalchemy import SQLAlchemy
import os

from marshmallow_sqlalchemy import SQLAlchemyAutoSchema
from marshmallow import fields

BASE_DIR = os.path.dirname(__file__)

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///{}'.format(os.path.join(BASE_DIR, 'rest.db'))


db = SQLAlchemy(app)

class Author (db.Model):
  id = db.Column(db.Integer, primary_key = True)
  name = db.Column(db.String(20))
  specialisation = db.Column(db.String(50))
  
  def __init__(self, name, specialisation):
    self.name = name
    self.specialisation = specialisation
    db.create_all()
  def __repr__(self):
    return '<Product %d>' % self.id
  

class AuthorSchema(SQLAlchemyAutoSchema):
  class Meta(SQLAlchemyAutoSchema.Meta):
    model = Author
    sqla_session = db.session
  id = fields.Number(dump_only = True)
  name = fields.String(required = True)
  specialisation = fields.String(required=True)
  
@app.route('/')
def hello_world():
  return 'Hello World!'

@app.route('/authors', methods = ['GET'])
def index():
  get_authors = Author.query.all()
  author_schema = AuthorSchema(many = True)
  authors, error = author_schema.dump(get_authors)
  return make_response(jsonify({"authors" : authors}))

if __name__ == "__main__":
  pass