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
conn = sqlite3.connect('weather_station.db')

cursor = conn.cursor()
cursor.execute("""
CREATE TABLE IF NOT EXISTS weather(
     name INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
     temp INTEGER,
     humid INTEGER,
     date DATETIME2
)
""")
conn.commit()


app._static_folder = os.path.abspath('')

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

@app.route("/", methods=['POST'])
def data():
    if request.method=='POST':
        body = request.json
        if body == None:
            return "not a json"
        if 'data' in body.keys():
            decodage = decode(body['data'][1])
            temperature = int(decodage[0])
            humidity = int (decodage[1])
            cursor.execute("""
                INSERT INTO weather(temp, humid, date) VALUES(?, ?, SYSDATETIME ())""", (temperature, humidity))
            print(body['data'][1])
        return jsonify(body)


@app.route("/", methods=['GET'])
def root():
	return send_file(filename_or_fp = "index.html", mimetype = "text/html")


@app.route("/releve", methods=['GET'])
def getreleve():
	if request.method=='GET':
		cursor.execute("""SELECT name, temp, humid, date FROM weather""")
        releves = cursor.fetchall()
        return jsonify(releves)


app.run(debug=True)
