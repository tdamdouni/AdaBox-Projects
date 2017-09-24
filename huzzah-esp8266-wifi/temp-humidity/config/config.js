'use strict'
const path = require('path')
const rootPath = path.normalize(__dirname + '/..')
const env = process.env.NODE_ENV || 'development'
const port = 1337

var config = {
  development: {
    root: rootPath,
    app: {
      name: 'temp-hum'
    },
    port: port,
    db: 'mongodb://localhost/temp-hum-development'
  },

  test: {
    root: rootPath,
    app: {
      name: 'temp-hum'
    },
    port: process.env.PORT || port,
    db: 'mongodb://localhost/temp-hum-test'
  },

  production: {
    root: rootPath,
    app: {
      name: 'temp-hum'
    },
    port: process.env.PORT || port,
    db: 'mongodb://localhost/temp-hum-production'
  }
};

module.exports = config[env];
