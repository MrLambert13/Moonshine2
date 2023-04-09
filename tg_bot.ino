#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

unsigned long bot_lasttime;           // время последнего входящего сообщения в ТГ
const unsigned long BOT_MTBS = 1000;  // время опроса входящих сообщений
String sendMsg;                       //переменная для сообщений
WiFiClientSecure telegramClient;
UniversalTelegramBot bot(BOT_TOKEN, telegramClient);

void initTGBot() {
  telegramClient.setInsecure();
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
  }
  BOT_SEND(answer);
}

/*Команды чата для бота
/blynk - Connect to Blynk
/status - System and sensors info
/sensinit - Initialize sensors
/templim - Setup start temp notifycation
/waterOff - Close tap
/waterOn - Open tap
/boilOn - 220 ON
/boilOff - 220 OFF
/stop - Stop system, close tap 
*/
void bot_setup() {
  const String commands = F("[{\"command\":\"blynk\",\"description\":\"Connect to Blynk\"},"
                            // "{\"command\":\"status\",\"description\":\"System and sensors info\"},"
                            // "{\"command\":\"sensinit\",\"description\":\"Initialize sensors\"},"
                            // "{\"command\":\"templim\",\"description\":\"Setup start temp notifycation\"},"
                            // "{\"command\":\"waterOff\",\"description\":\"Close tap\"},"
                            // "{\"command\":\"waterOn\",\"description\":\"Open tap\"},"
                            // "{\"command\":\"boilOn\",\"description\":\"220 ON\"},"
                            "{\"command\":\"boilOff\",\"description\":\"220 OFF\"},"
                            "{\"command\":\"stop\",\"description\":\"Stop system, close tap\"}]");
  bot.setMyCommands(commands);
}