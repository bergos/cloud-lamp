#include <ArduinoJson.h>
#include <ESPSimpleHttpClient.h>
#include "cloud-lamp.h"
#include "cloud-leds.h"
#include "cloud-mode-cloud.h"
#include "cloud-settings.h"
#include "color.h"

void CloudLampModeCloud::begin(CloudLamp* lamp) {
  this->lamp = lamp;

  for (uint16_t i=0; i<lamp->leds->number; i++) {
    lamp->leds->setPixel(i, 0);
  }

  lamp->leds->show();
}

void CloudLampModeCloud::loop() {
  if (lamp->settings->cloudUrl.length() == 0) {
    return;
  }

  ESPSimpleHttpClient http;

  http.begin(lamp->settings->cloudUrl, lamp->settings->cloudUser, lamp->settings->cloudPassword);
  http.addHeader("Accept", "application/json");

  int error = http.get();

  DynamicJsonBuffer jsonBuffer;

  JsonObject& json = jsonBuffer.parseObject(http.bodyStream());

  http.end();

  JsonArray& colors = json["color"];

  uint16_t i = 0;

  for(JsonArray::iterator it=colors.begin(); it!=colors.end(); ++it) {
    String colorString = it->as<String>();
    uint32_t color = colorFromCss(colorString);

    lamp->leds->setPixel(i++, color);
  }

  lamp->leds->show();
}

