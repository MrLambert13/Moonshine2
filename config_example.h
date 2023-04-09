#define SSID_MAIN ""
#define SSID_DEBUG ""
#define WIFI_PASSWORD ""
#define BLYNK_TOKEN ""
#define BLYNK_SERVER ""
#define BOT_TOKEN ""
#define CHAT_ID ""

//переименовать файл в config.h

/*********************************************************/
//Для отладки, меняем сеть и делаем выводы в монитор
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_BEGIN(x) Serial.begin(x)
#define MYSSID SSID_DEBUG
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_BEGIN(x)
#define MYSSID SSID_MAIN
#endif
/*********************************************************/