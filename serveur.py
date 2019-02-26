from flask import Flask, send_file
from flask import request
from flask import render_template
from flask import jsonify
import sqlite3
import datetime
from flask_cors import CORS
import os

app = Flask(__name__, static_url_path='')
CORS(app)

temperature = []
humidity = []

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

def decode(receivedData):
    if(len(receivedData)!=8):
        return -1,-1

    odd = False
    data = []

    for number in receivedData:
        if(odd):
            data += number
        odd = not odd

    return data[0]+data[1], data[2]+data[3]

decodage = decode("32343139")
temperature.append(decodage[0])
humidity.append(decodage[1])


@app.route("/", methods=['GET'])
def root():
	return send_file(filename_or_fp = "index.html", mimetype = "text/html")


@app.route("/releve", methods=['GET'])
def getreleve():
	if request.method=='GET':
		releves = [
		{'name': 1, 'temp': temperature[0], 'humid': humidity[0], 't': datetime.datetime.utcnow()},
		{'name': 2, 'temp': 7, 'humid': 8, 't': datetime.datetime.utcnow()},
		{'name': 3, 'temp': 9, 'humid': 9, 't': datetime.datetime.utcnow()}
		]
		return jsonify(releves)


app.run(debug=True)
