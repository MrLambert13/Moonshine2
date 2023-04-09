#include <UniversalTelegramBot.h>

extern UniversalTelegramBot bot;
extern String sendMsg;                                       //переменная для сообщений

#define BOT_SEND(x) bot.sendMessage(CHAT_ID, x)  //упрощённый вызов отправки сообщений
