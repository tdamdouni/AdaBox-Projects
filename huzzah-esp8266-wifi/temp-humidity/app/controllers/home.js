'use strict'
const express = require('express')
const router = express.Router()
const mongoose = require('mongoose')
const TempHumidity = mongoose.model('TempHumidity')
let Netcat = require('node-netcat');
let server = Netcat.server(5000);

server.on('ready', function() {
    console.log('server ready');
  });

  server.on('data', function(client, data) {
      console.log('server rx: ' + data + ' from ' + client);
  });

  server.on('client_on', function(client) {
      console.log('client on ', client);
  });

  server.on('client_of', function(client) {
      console.log('client off ', client);
  });

  server.on('error', function(err) {
      console.log(err);
  });

  server.on('close', function() {
      console.log('server closed');
  });

  server.listen(); // start to listening


module.exports = function (app) {
  app.use('/', router);
};

router.get('/', function (req, res, next) {
  TempHumidity.find(function (err, measures) {
    if (err) return next(err);
    res.render('index', {
      title: 'Temperarue and humidity measurments',
      measures: measures
    })
  })
})

router.get('/add', function (req, res, next) {

  let tempHum = new TempHumidity({
    temp: '22',
    humidity: '67',
    time: '2016-09-04 23:31'
  })

  // tempHum.save(function(err, thor) {
  //   if (err) return console.error(err);
  //   console.dir(tempHum);
  // });
})