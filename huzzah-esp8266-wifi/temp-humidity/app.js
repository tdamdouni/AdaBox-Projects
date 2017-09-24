'use strict'

const express = require('express')
const config = require('./config/config')
const glob = require('glob')
const mongoose = require('mongoose')

// Use native promises
mongoose.Promise = global.Promise;

mongoose.connect(config.db)
const db = mongoose.connection

db.once('open', function() {
  console.log('Connected to MongoDb')
});

db.on('error', function () {
  throw new Error('unable to connect to database at ' + config.db)
});

const models = glob.sync(config.root + '/app/models/*.js')
models.forEach(function (model) {
  require(model)
})

const app = express()

require('./config/express')(app, config)

app.listen(config.port, function () {
  console.log('Express server listening on port ' + config.port)
})

