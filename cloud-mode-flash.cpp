#include "cloud-lamp.h"
#include "cloud-leds.h"
#include "cloud-mode-flash.h"
#include "cloud-settings.h"

void CloudLampModeFlash::begin(CloudLamp* lamp) {
  this->lamp = lamp;

  for (uint16_t i=0; i<lamp->leds->number; i++) {
    lamp->leds->setPixel(i, lamp->settings->primaryColor);
  }

  lamp->leds->show();
}

void CloudLampModeFlash::loop() {
  uint16_t t = millis() % 2304;

  uint8_t r, g, b;

  if (t < 256) {
    r = g = t / 2;
    b = t;
  } else {
    b = (2304 - t) / 8;
    r = g = b / 2;
  }

  for (uint16_t i=0; i<lamp->leds->number; i++) {
    lamp->leds->setPixel(i, r, g, b);
  }

  lamp->leds->show();
}
