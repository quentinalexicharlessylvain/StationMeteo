from flask import Flask
from flask import request
from flask import render_template
from flask import jsonify
import sqlite3
import datetime
from flask_cors import CORS
import os
app = Flask(__name__, static_url_path='')
CORS(app)

app._static_folder = os.path.abspath('')


# @app.route("/", methods=['POST'])
# def data():
# 	if request.method=='POST':
# 		body = request.json
# 		if body == None:
# 			return "not a json"
# 		if 'data' in body.keys():
# 			print(body['data'][1])
# 		return jsonify(body)

@app.route("/")
def root():
	root_dir = os.path.dirname(os.getcwd())
	return app.send_from_diretory(root_dir, "index.html")


@app.route("/temps", methods=['GET'])
def gettemp():
	if request.method=='GET':
		temperatures = [
		{'data': 5, 't': datetime.datetime.utcnow()},
		{'data': 5, 't': datetime.datetime.utcnow()},
		{'data': 5, 't': datetime.datetime.utcnow()}
		]
		return jsonify(temperatures)

app.run(debug=True)
