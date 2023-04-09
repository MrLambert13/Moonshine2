#include <ESP8266WiFi.h>
#include "tg_bot.h"

void initWiFi(){
  WiFi.begin(MYSSID, WIFI_PASSWORD);
  connectToWifi();
}

void connectToWifi() {
  DEBUG_PRINT("Подключение к " + String(MYSSID));
  while (!isWiFiConnected()) {
    delay(1000);
    DEBUG_PRINT(".");
  }

  BOT_SEND("Wifi подключен");
  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINTLN("Wifi подключен");
}

bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void WiFiControl() {
  if (!isWiFiConnected()) {
    connectToWifi();
  }
}