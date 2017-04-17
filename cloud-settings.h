#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <Arduino.h>

class AsyncWebServerRequest;
class CloudLamp;
class CloudLampMode;

class CloudLampSettings {
  public:
    uint32_t primaryColor = 0xffffff;
    String mode;
    String cloudUrl;
    String cloudUser;
    String cloudPassword;
    bool cloudPush;

    CloudLampSettings();

    void begin(CloudLamp* lamp);

    void get(AsyncWebServerRequest* request);

    void put(AsyncWebServerRequest* request, uint8_t* data, size_t len);

  protected:
    CloudLamp* lamp;

    void updateMode();
};

#endif // _SETTINGS_H
