var basicAuth = require('express-basic-auth')
var bodyParser = require('body-parser')
var express = require('express')
var fs = require('fs')
var merge = require('lodash/merge')
var morgan = require('morgan')
var modes = require('./modes')
var path = require('path')

function loadJson (filename) {
  try {
    return JSON.parse(fs.readFileSync(path.resolve(filename)).toString())
  } catch(e) {
    return null
  }
}

var config = merge(loadJson('config.default.json'), loadJson('config.json'))

var leds = config.leds
var settings = config.settings

var app = express()

for (var i = 0; i < 60; i++) {
  leds.color.push('#000000')
}

function validateSettings (settings) {
  return {
    cloudPassword: settings.cloudPassword || '',
    cloudPush: settings.cloudPush ? true : false,
    cloudUrl: settings.cloudUrl || '',
    cloudUser: settings.cloudUser || '',
    mode: settings.mode || 'server',
    primaryColor: settings.primaryColor || '#000000'
  }
}

if (config.logging) {
  app.use(morgan('common'))
}

app.use(basicAuth({
  users: config.users,
  challenge: true,
  realm: 'Cloud-Lamp'
}))

app.use(bodyParser.json())

app.get('/leds', function (req, res) {
  console.log(req.headers)

  res.json(leds)
})

app.put('/leds', function (req, res) {
  leds = req.body

  res.json(leds)
})

app.get('/settings', function (req, res) {
  res.json(settings)
})

app.put('/settings', function (req, res) {
  settings = validateSettings(req.body)

  res.json(settings)
})

app.use(express.static(path.resolve(__dirname, '../../data')))

app.listen(3002, function () {
  console.log('Cloud Lamp simulator running at http://localhost:' + this.address().port + '/')
})

function loop () {
  if (settings.mode in modes) {
    modes[settings.mode](leds, settings)
  }

  setTimeout(loop, 1000 / 50)
}

loop()
