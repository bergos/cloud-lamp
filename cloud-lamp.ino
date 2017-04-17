#include <ESP8266mDNS.h>
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

  // mDNS service
  Serial.print("init mDNS...");
  if (!MDNS.begin("cloud-lamp")) {
    Serial.println("failed");
  } else {
    Serial.println("done");
    MDNS.addService("http", "tcp", 80);
  }
}

void loop() {
  cloudLamp.loop();
}

