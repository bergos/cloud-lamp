#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <ESPSimpleHttpClient.h>
#include <NeoPixelBus.h>
#include "cloud-lamp.h"
#include "cloud-leds.h"
#include "cloud-settings.h"
#include "color.h"

CloudLampLeds::CloudLampLeds(uint16_t number, uint8_t rows) : number(number), rows(rows) {
  columns = ceil((float)number / (float)rows);

  strip = new NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod>(number, 0);
}

CloudLampLeds::~CloudLampLeds() {
  delete strip;
}

void CloudLampLeds::begin(CloudLamp* lamp) {
  this->lamp = lamp;

  lamp->server->on("/leds", HTTP_GET, [this](AsyncWebServerRequest* request) {
    Serial.println("GET /leds");

    get(request);
  });

  lamp->server->on("/leds", HTTP_PUT, [](AsyncWebServerRequest* request) {
  }, [](AsyncWebServerRequest* request, String filename, size_t index, uint8_t* data, size_t len, bool final) {
  }, [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
    Serial.println("PUT /leds");

    put(request, data, len);
  });

  strip->Begin();
}

void CloudLampLeds::toJson(char* content, size_t contentLength) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& json = jsonBuffer.createObject();

  json["rows"] = rows;
  json["columns"] = columns;

  JsonArray& color = json.createNestedArray("color");

  for(uint16_t i=0; i<number; i++) {
    color.add(colorToCss(getPixel(i)));
  }

  json.printTo(content, contentLength);
}

uint32_t CloudLampLeds::getPixel(uint16_t index) {
  HtmlColor htmlColor = strip->GetPixelColor(index);

  return htmlColor.Color;
}

void CloudLampLeds::setPixel(uint16_t index, uint32_t color) {
  strip->SetPixelColor(index, HtmlColor(color));
}

void CloudLampLeds::setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t color = (red << 16) | (green << 8) | blue;

  setPixel(index, color);
}

void CloudLampLeds::show() {
  strip->Show();  
  push();
}

void CloudLampLeds::get(AsyncWebServerRequest* request) {
  char content[700];

  toJson(content, sizeof(content));

  AsyncWebServerResponse* response = request->beginResponse(200, "application/json", content);
  request->send(response);
}

void CloudLampLeds::put(AsyncWebServerRequest* request, uint8_t* data, size_t len) {
  get(request);
}

  

void CloudLampLeds::push() {
  if (!lamp->settings->cloudPush || lamp->settings->cloudUrl.length() == 0) {
    return;
  }

  char content[700];

  toJson(content, sizeof(content));

  ESPSimpleHttpClient http;

  http.begin(lamp->settings->cloudUrl, lamp->settings->cloudUser, lamp->settings->cloudPassword);
  http.addHeader("Content-Type", "application/json");

  int error = http.put(content);

  /*if(error != ESPSimpleHttpClient::ERROR_NONE) {
    Serial.print("PUT failed with error: ");
    Serial.println(error);
  }*/

  http.end();
}

