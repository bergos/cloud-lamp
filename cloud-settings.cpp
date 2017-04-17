#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include "cloud-lamp.h"
#include "cloud-mode-flash.h"
#include "cloud-mode-solid.h"
#include "cloud-mode-cloud.h"
#include "cloud-settings.h"
#include "color.h"

CloudLampSettings::CloudLampSettings() : mode("solid") {
}

void CloudLampSettings::begin(CloudLamp* lamp) {
  this->lamp = lamp;

  lamp->server->on("/settings", HTTP_GET, [this](AsyncWebServerRequest* request) {
    Serial.println("GET /settings");

    get(request);
  });

  lamp->server->on("/settings", HTTP_PUT, [](AsyncWebServerRequest* request) {
  }, [](AsyncWebServerRequest* request, String filename, size_t index, uint8_t* data, size_t len, bool final) {
  }, [this](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
    Serial.println("PUT /settings");

    put(request, data, len);
  });

  updateMode();
}

void CloudLampSettings::get(AsyncWebServerRequest* request) {
  char content[200];
  DynamicJsonBuffer jsonBuffer;

  JsonObject& json = jsonBuffer.createObject();
  json["mode"] = mode;
  json["primaryColor"] = colorToCss(primaryColor);

  json.printTo(content, sizeof(content));

  AsyncWebServerResponse* response = request->beginResponse(200, "application/json", content);
  request->send(response);
}

void CloudLampSettings::put(AsyncWebServerRequest* request, uint8_t* data, size_t len) {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& json = jsonBuffer.parseObject(data);

  if (!json.success()) {
    Serial.println("invalid JSON object");

    AsyncWebServerResponse* response = request->beginResponse(400);
    request->send(response);

    return;
  }

  primaryColor = colorFromCss(json["primaryColor"]);
  mode = json.get<String>("mode");
  cloudUrl = json.get<String>("cloudUrl");
  cloudUser = json.get<String>("cloudUser");
  cloudPassword = json.get<String>("cloudPassword");
  cloudPush = json.get<String>("cloudPush") == "on";

  updateMode();

  get(request);
}


void CloudLampSettings::updateMode() {
  CloudLampMode* mode = 0;

  if (this->mode == "solid") {
    mode = new CloudLampModeSolid();
  } else if (this->mode == "flash") {
    mode = new CloudLampModeFlash();
  } else if (this->mode == "cloud") {
    mode = new CloudLampModeCloud();
  }

  if (!mode) {
    return;
  }

  if (lamp->mode) {
    delete lamp->mode;
  }

  lamp->mode = mode;
  lamp->mode->begin(lamp);
}

