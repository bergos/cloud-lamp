#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include "cloud-lamp.h"

#define LED_NUMBER 60
#define LED_ROWS 7

CloudLamp cloudLamp(LED_NUMBER, LED_ROWS);

void setup() {
  Serial.begin(115200);

  // init WiFi
  WiFiManager wifiManager;

  wifiManager.autoConnect("cloud-lamp-ap");

  // cloud lamp server and leds
  cloudLamp.begin();

  Serial.println("http://" + WiFi.localIP().toString() + "/");
}

void loop() {
  cloudLamp.loop();
}

