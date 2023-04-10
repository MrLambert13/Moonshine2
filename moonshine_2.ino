#include "config.h"
#include "tg_bot.h"
#include "MyDallas.h"

void setup() {
  DEBUG_BEGIN(115200);

  connectToWifi();
  initTGBot();

  BOT_SEND("Система запущена");

  sensorsInit();
}

void loop() {
  handleOTA();
  checkNewMsg();  //проверка сообщений ТГ ботом
}
