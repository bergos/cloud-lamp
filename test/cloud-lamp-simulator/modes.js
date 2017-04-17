var colorString = require('color-string')

function modeCloud (leds, settings) {
  // TODO:
}

function modeSolid (leds, settings) {
  leds.color.forEach(function (color, index) {
    leds.color[index] = settings.primaryColor
  })
}

function clampInt (value, min, max) {
  min = min || 0
  max = max || 255

  return Math.floor(Math.max(min, Math.min(max, value)))
}

function modeFlash (leds, settings) {
  var t = (new Date()).valueOf() % 5000

  var l = 0

  if (t < 256) {
    l = Math.pow(t, 2) / 255
  } else if (t < 512) {
    l = Math.pow(512 - t, 2) / 255
  }

  leds.color.forEach(function (color, index) {
    leds.color[index] = colorString.to.hex([
      clampInt(l / 3),
      clampInt(l / 3),
      clampInt(l / 2)])
  })
}

function modeServer (leds, settings) {
}

module.exports = {
  cloud: modeCloud,
  solid: modeSolid,
  flash: modeFlash,
  server: modeServer
}
