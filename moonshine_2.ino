#include "config.h"
#include "tg_bot.h"

void setup() {
  DEBUG_BEGIN(115200);

  connectToWifi();
  initTGBot();

  BOT_SEND("Система запущена");
}

void loop() {
  handleOTA();
  checkNewMsg();  //проверка сообщений ТГ ботом
}
