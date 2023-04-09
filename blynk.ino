#include <BlynkSimpleEsp8266.h>
#include "tg_bot.h"

#define BLYNK_PRINT Serial                         // хз зачем Serial для блинка

void initBlynk(){
  Blynk.config(BLYNK_TOKEN, BLYNK_SERVER, 8080); 
}

/*Подключение к Blynk*/
bool ConnectBlynk(void) {
  bool state = true;  //заведомо считаем успешным подключение
  int i = 0;          //счетчик попыток
  while (Blynk.connected() != true) {
    sendMsg = "Подключение к Blynk. Попытка №" + String(i + 1);
    DEBUG_PRINTLN(sendMsg);
    BOT_SEND(sendMsg);
    Blynk.connect(3000);
    if (i > 3) {  //3 попытки по 3 секунды
      state = false;
      break;
    }
    i++;
  }
  
  if (state) {
    sendMsg = "Blynk подключен";
  } else {
    sendMsg = "Не удалось подключится к Blynk";
  }
  DEBUG_PRINTLN(sendMsg);
  BOT_SEND(sendMsg);
  return state;
}