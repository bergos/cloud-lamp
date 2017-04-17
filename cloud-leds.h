#ifndef _CLOUD_LEDS_H
#define _CLOUD_LEDS_H

#include <NeoPixelBus.h>

class AsyncWebServerRequest;
class CloudLamp;

class CloudLampLeds {
  public:
    uint16_t number;
    uint8_t rows;
    uint8_t columns;

    CloudLampLeds(uint16_t number, uint8_t rows);
    virtual ~CloudLampLeds();

    void begin(CloudLamp* lamp);

    void toJson(char* content, size_t contentLength);

    uint32_t getPixel(uint16_t index);

    void setPixel(uint16_t index, uint32_t color);
    void setPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

    void show();

    void get(AsyncWebServerRequest* request);

    void put(AsyncWebServerRequest* request, uint8_t* data, size_t len);

    void push();

  protected:
    CloudLamp* lamp;
    NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod>* strip;
};

#endif // _CLOUD_LEDS_H
