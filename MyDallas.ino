#include <OneWire.h>               // библиотека для работы датчиков по одному пину
#include <DallasTemperature.h>     // для работы с DS18B20

//параметры для датчиков температуры
#define ONE_WIRE_BUS 5                // пин подключения 1-wire
OneWire oneWire(ONE_WIRE_BUS);        // создание объекта onewire
DallasTemperature sensors(&oneWire);  // объект для работы с DallasTemperature
DeviceAddress *sensorsUnique;         // массив для получения любого количества датчиков

//ручная адрессация датчиков, чтобы обращаться за нужной температурой руками. Т.к. хз как автоматизировать
DeviceAddress cubeTermometer = { 0x28, 0xbb, 0xfb, 0xfb, 0xc0, 0x21, 0x09, 0x18 };
DeviceAddress pipeTermometer = { 0x28, 0xd9, 0x01, 0x36, 0x2e, 0x21, 0x01, 0xfb };
DeviceAddress upperTermometer = { 0x28, 0x04, 0x24, 0x38, 0x2e, 0x21, 0x01, 0x4a };
DeviceAddress waterTermometer = { 0x28, 0x0e, 0x6c, 0x57, 0x04, 0x5d, 0x3c, 0x1e };
DeviceAddress insideTermometer = { 0x28, 0x0b, 0xa8, 0x49, 0xf6, 0xb2, 0x3c, 0x4a };

int countSensors;                            // количество датчиков DS18B20
float temps[5];                              // массив для хранения текущих температур
int lastSndTemp[5];                          // массив для хранения температур о которых последний раз оповещали
int CUBE_TEMP_LIM = 70;                      // температура куба с которой начинаются все оповещения в ТГ по температуре
int END_CUBE_TEMP = 98;                      // температура окончания работы (98 для подстила, 96 для ректификации)
int WATER_TEMP_MAX = 50;                     // макс поддерживаемая температура проточной воды на выходе с холодильника
int WATER_TEMP_ERR = 60;                     // температура при которой система уйдет в защиту
int WATER_TEMP_MIN = 40;                     // минимальная поддерживаемая температура проточной воды на выходе с холодильника
unsigned long lastTimeSensUpd;               // последнее время запроса температур с датчиков
const unsigned long SENSOR_TIME_UPD = 5000;  // время опроса датчиков температуры

/*Расшифровка адресов датчиков температуры в HEX*/
String printAddress(DeviceAddress deviceAddress) {
  String adress;
  for (uint8_t i = 0; i < 8; i++) {
    adress += "0x";
    if (deviceAddress[i] < 16) adress += "0";
    adress += String(deviceAddress[i], HEX);
    if (i < 7) adress += ", ";
  }
  return adress;
}

/*Инициализация датчиков DS18B20*/
void sensorsInit() {
  sensors.begin();

  countSensors = sensors.getDeviceCount();  //find all devices on wire
  sendMsg = "Найдено датчиков: " + String(countSensors);

  sensorsUnique = new DeviceAddress[countSensors];

  //Получение HEX адресов датчиков
  for (int i = 0; i < countSensors; i++) {
    sensors.getAddress(sensorsUnique[i], i);
    sendMsg += "\nДатчик " + String(i) + " - адрес: " + printAddress(sensorsUnique[i]);
    sensors.setResolution(sensorsUnique[i], 11);  //Разрешение датчиков
  }

  DEBUG_PRINTLN(sendMsg);
  BOT_SEND(sendMsg);
}

/*Получить температуру всех датчиков*/
void getTemps() {
  sensors.requestTemperatures();
  for (int i = 0; i < countSensors; i++) {
    temps[i] = sensors.getTempCByIndex(i);
    DEBUG_PRINTLN(String(printAddress(sensorsUnique[i])).substring(36) + " - " + temps[i]);
  }
}

/*Уведомления по температуре*/
void tempNotify(bool all = false) {
  float cubeT = sensors.getTempC(cubeTermometer);
  // if (cubeT > END_CUBE_TEMP) boilEnd();
  if (cubeT < CUBE_TEMP_LIM && cubeT != -127) return;
  for (byte i = 0; i < countSensors; i++) {
    //if alrady notify this temp or less then CUBE_TEMP_LIM - break
    if (!all && (int(temps[i]) == lastSndTemp[i])) continue;
    //main notify IF
    if ((int(temps[i]) % 5 == 0 || !lastSndTemp[i] || lastSndTemp[i] - temps[i] > 4) && temps[i] > CUBE_TEMP_LIM || all) {
      String str = "Sensor " + String(i) + ": " + temps[i];
      BOT_SEND(str);
      lastSndTemp[i] = int(temps[i]);
    }
  }
}

//Обновление температуры по таймауту
void tempsUpdate(){
  if (millis() - lastTimeSensUpd > SENSOR_TIME_UPD) {
    getTemps();
    tempNotify();
    lastTimeSensUpd = millis();
  }
}