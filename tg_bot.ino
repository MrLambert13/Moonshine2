#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

unsigned long bot_lasttime;           // время последнего входящего сообщения в ТГ
const unsigned long BOT_MTBS = 1000;  // время опроса входящих сообщений
String sendMsg;                       //переменная для сообщений
WiFiClientSecure telegramClient;
UniversalTelegramBot bot(BOT_TOKEN, telegramClient);

void initTGBot() {
  telegramClient.setInsecure();
  bot_setup();
  DEBUG_PRINTLN("Бот настроен");
}

void checkNewMsg() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}

/*Handle incomming messages in TG*/
void handleNewMessages(int numNewMessages) {
  String answer;
  for (int i = 0; i < numNewMessages; i++) {
    telegramMessage &msg = bot.messages[i];

    if (msg.text == "/1") heatRelay.toggle();
    if (msg.text == "/2") C2H5OHRelay.toggle();
    if (msg.text == "/3") waterRelay.toggle();
  }
  BOT_SEND(answer);
}

/*Команды чата для бота
/blynk - Подключение к серверу Blynk
/status - Получить данные с датчиков
/sensinit - Провести заного иниц-ю датчиков
/templim - Установить температуру начала оповещений
/waterOff - Закрыть воду
/waterOn - Открыть воду
/boilOn - Включить нагрузку 220
/boilOff - Выключить нагрузку 220
/stop - Остановить систему
*/
void bot_setup() {
  const String commands = F("[{\"command\":\"blynk\",\"description\":\"Подключение к серверу Blynk\"},"
                            "{\"command\":\"status\",\"description\":\"Получить данные с датчиков\"},"
                            "{\"command\":\"templim\",\"description\":\"Установить температуру начала оповещений\"},"
                            "{\"command\":\"sensinit\",\"description\":\"Провести заного иниц-ю датчиков\"},"
                            "{\"command\":\"waterOff\",\"description\":\"Закрыть воду\"},"
                            "{\"command\":\"waterOn\",\"description\":\"Открыть воду\"},"
                            "{\"command\":\"stop\",\"description\":\"Остановить систему\"}]");
  bot.setMyCommands(commands);
}