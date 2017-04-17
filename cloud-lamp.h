#ifndef _CLOUD_LAMP_H
#define _CLOUD_LAMP_H

#include <Arduino.h>

class AsyncWebServer;
class CloudLampLeds;
class CloudLampMode;
class CloudLampSettings;

class CloudLamp {
  public:
    AsyncWebServer* server = 0;
    CloudLampSettings* settings = 0;
    CloudLampLeds* leds = 0;
    CloudLampMode* mode = 0;

    CloudLamp(uint16_t number, uint8_t rows);
    virtual ~CloudLamp();

    void begin();

    void loop();
};

#endif // _CLOUD_LAMP_H

