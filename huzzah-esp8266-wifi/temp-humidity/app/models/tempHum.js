'use strict'

const mongoose = require('mongoose')
const Schema = mongoose.Schema;

const TempHumiditySchema = new Schema({
  temp: String,
  humidity: String,
  time: String
});

mongoose.model('TempHumidity', TempHumiditySchema);