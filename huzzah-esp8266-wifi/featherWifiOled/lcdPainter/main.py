import flask
import json
import os

from flask import Flask
from flask import request
from flask import render_template

app = Flask(__name__)

@app.route("/")
def default():
    return render_template("index.html")

@app.route("/saveData", methods=['POST'])
def saveData():
	data=request.form['d']
	f = open("current.txt","w")
	f.write(data)
	f.close()
	return ""

@app.route("/loadData")
def loadData():
	data = open("current.txt").read()
	return data

if __name__ == "__main__":
    appHost = int(os.environ['APP_HOST']) if 'APP_HOST' in os.environ else '0.0.0.0'
    appPort = int(os.environ['APP_PORT']) if 'APP_PORT' in os.environ else 5002
    app.run(debug=True, host=appHost,port=appPort)
