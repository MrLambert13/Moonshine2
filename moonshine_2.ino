#include "config.h"
#include "tg_bot.h"
#include "MyDallas.h"
#include "MyRelay.h"
#include "MyStepper.h"

/*Занятые пины
GPIO13 - D7 - DIR для шагового двигателя
GPIO12 - D6 - STEP для шагового
GPIO14 - D5 - Включение для шагового
GPIO5 - D1 - Датчики температуры
GPIO4 - D2 - Реле нагрева
GPIO0 - D3 - Реле отбора жидкости
GPIO2 - D4 - Реле отбора жидкости
*/
#define HEAT_RELAY_PIN 4
#define C2H5OH_RELAY_PIN 0
#define WATER_RELAY_PIN 2
#define STEP_DIR_PIN 13
#define STEP_STEP_PIN 12
#define STEP_EN_PIN 14
#define ONE_WIRE_PIN 5

//Создаем объекты реле
MyRelay heatRelay(HEAT_RELAY_PIN, "Нагрузка", false, true);
MyRelay C2H5OHRelay(C2H5OH_RELAY_PIN, "Узел отбора", false, true);
MyRelay waterRelay(WATER_RELAY_PIN, "Вода", false, true);

//Создание объекта шагового двигателя
MyStepper waterMotor(STEP_DIR_PIN, STEP_STEP_PIN, STEP_EN_PIN, 360, 2000, 1.8, false, true, true);

//создание структуры датчиков
struct mySensor {
  DeviceAddress adress;
  float temp;
  float lastNotifyTemp;
  bool isConnected;
};

//объявление датчиков
mySensor cubeSens;

void setup() {
  DEBUG_BEGIN(115200);

  connectToWifi();
  initTGBot();

  BOT_SEND("Система запущена");

  sensorsInit();
}

void loop() {
  //handleOTA();
  checkNewMsg();  //проверка сообщений ТГ ботом
}
