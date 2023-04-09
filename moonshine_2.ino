#include "config.h"
#include "tg_bot.h"

extern UniversalTelegramBot bot;

void setup() {
  DEBUG_BEGIN(115200);

  initWiFi();
  initTGBot();
  initBlynk();
  // connectToWifi();
  ConnectBlynk();
}

void loop() {
  checkNewMsg();  //проверка сообщений ТГ ботом
}
