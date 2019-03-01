from flask import Flask, send_file
from flask import request
from flask import render_template
from flask import jsonify
import sqlite3
import datetime
from flask_cors import CORS
import os

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

def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

app = Flask(__name__, static_url_path='')
CORS(app)
conn = sqlite3.connect('weather_station.db', check_same_thread=False)
conn.row_factory = dict_factory
cursor = conn.cursor()
cursor.execute('''
CREATE TABLE IF NOT EXISTS weather(
     name INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
     temp INTEGER,
     humid INTEGER,
     date VARCHAR
)
''')



app._static_folder = os.path.abspath('')



@app.route("/", methods=['POST'])
def data():
    if request.method=='POST':
        body = request.json
        if body == None:
            return "not a json"
        if 'data' in body.keys():
            decodage = decode(body['data'])
            temperature = int(decodage[0])
            humidity = int (decodage[1])
            date = datetime.datetime.utcnow()
            cursor.execute('''
                INSERT INTO weather(temp,humid,date) VALUES(?,?,?)''', (temperature, humidity, date))
            cursor.execute("""SELECT name, temp, humid, date FROM weather""")
            releves = cursor.fetchall()
            print(releves)
            print(body['data'])
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
conn.commit()
conn.close()
