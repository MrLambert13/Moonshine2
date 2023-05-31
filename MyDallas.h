#include <OneWire.h>
#include <DallasTemperature.h>

// Создаем объект для работы с шиной OneWire
extern OneWire oneWire;

// Создаем объект для работы с датчиками DS18B20
extern DallasTemperature sensors;

void sensorsInit();

void getTemps();
