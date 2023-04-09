#include <ESP8266WiFi.h>
#include "tg_bot.h"

void connectToWifi() {
  WiFi.begin(MYSSID, WIFI_PASSWORD);
  DEBUG_PRINT("Подключение к " + String(MYSSID));
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    DEBUG_PRINT(".");
  }

  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINTLN("Wifi подключен");
}

void WiFiControl() {
  //контроль отвала сети
}