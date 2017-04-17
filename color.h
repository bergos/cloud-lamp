#ifndef COLOR_H_
#define COLOR_H_

#include <Arduino.h>

uint32_t colorFromCss(String cssColor);

String byteToHex(uint8_t byte);

String colorToCss(uint32_t color);

#endif // COLOR_H_
