#include "cloud-lamp.h"
#include "cloud-leds.h"
#include "cloud-mode-solid.h"
#include "cloud-settings.h"

void CloudLampModeSolid::begin(CloudLamp* lamp) {
  this->lamp = lamp;

  for (uint16_t i=0; i<lamp->leds->number; i++) {
    lamp->leds->setPixel(i, lamp->settings->primaryColor);
  }

  lamp->leds->show();
}

void CloudLampModeSolid::loop() {
  for (uint16_t i=0; i<lamp->leds->number; i++) {
    lamp->leds->setPixel(i, lamp->settings->primaryColor);
  }

  lamp->leds->show();
}

