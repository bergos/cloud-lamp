#include <ESPAsyncWebServer.h>

#include "cloud-lamp.h"
#include "cloud-leds.h"
#include "cloud-mode.h"
#include "cloud-settings.h"

CloudLamp::CloudLamp(uint16_t number, uint8_t rows) {
  server = new AsyncWebServer(80);
  settings = new CloudLampSettings();
  leds = new CloudLampLeds(number, rows);  
}

CloudLamp::~CloudLamp() {
  delete server;
  delete settings;
  delete leds;
}

void CloudLamp::begin() {
  Serial.print("init SPIFFS...");
  SPIFFS.begin();
  Serial.println("done");

  Serial.print("init LEDs...");
  leds->begin(this);
  Serial.println("done");

  Serial.print("init settings...");
  settings->begin(this);
  Serial.println("done");

  Serial.print("init HTTP server...");  
  server->begin();
  server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  Serial.println("done");
}

void CloudLamp::loop() {
  if (mode) {
    mode->loop();
  }
}

