#include "Arduino.h"

#include <OneWire.h>
#include <DallasTemperature.h>
//float temp;

OneWire oneWire(14); //Podłączenie do pinu 13
DallasTemperature sensors(&oneWire); //Przekazania informacji do biblioteki
float temp1; //zmienna globalna

void temp_ds18b20() {
  sensors.begin(); //Inicjalizacja czujnikow
  // w pętli działa ta częśc kodu
//  sensors.requestTemperatures(); //Pobranie temperatury czujnika
  //temp = sensors.getTempCByIndex(0); // przypisanie pobranej temperatury
  //Serial.print("Aktualna temperatura: ");
  //Serial.println(temp);  //Wyswietlenie informacji

  //delay(500);
}
void readTemp() {
  temp_ds18b20(); // wywołanie odczytu czujnikow
  sensors.requestTemperatures(); //Pobranie temperatury czujnika
  temp1 = sensors.getTempCByIndex(0); // przypisanie pobranej temperatury
  //Serial.println("PRACA_TESTOWA");
  Serial.println(temp1);
  //delay(500);
}
