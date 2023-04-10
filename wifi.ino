#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include "tg_bot.h"

void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(MYSSID, WIFI_PASSWORD);

  DEBUG_PRINTLN("Подключение к " + String(MYSSID));
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    DEBUG_PRINTLN("Подключение не удалось. Перезагрузка системы...");
    delay(3000);
    ESP.restart();
  }
  DEBUG_PRINTLN(WiFi.localIP());
  DEBUG_PRINTLN("Wifi подключен");

  ArduinoOTA.setPassword("admin");

  // OTA setup
  ArduinoOTA.onStart([]() {
    DEBUG_PRINTLN("OTA Starting...");
  });
  ArduinoOTA.onEnd([]() {
    DEBUG_PRINTLN("OTA Done!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    DEBUG_PRINTLN("OTA Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    DEBUG_PRINTLN("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) DEBUG_PRINTLN("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) DEBUG_PRINTLN("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) DEBUG_PRINTLN("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) DEBUG_PRINTLN("Receive Failed");
    else if (error == OTA_END_ERROR) DEBUG_PRINTLN("End Failed");
  });
  ArduinoOTA.begin();
}

void WiFiControl() {
  //контроль отвала сети
}

void handleOTA() {
  ArduinoOTA.handle();
}