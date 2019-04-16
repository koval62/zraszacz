#include "Arduino.h"
#include "blink.h" // moja funkcja
//#include "wifirifi.h" // moja funkcja
#include "MyOTA.h"    // moja funkcja
//#include "temp_ds18b20.h"  // moja funkcja




///////////////////////////////////////////////
/////////////CZAS/////////////////////////////
unsigned long aktualnyCzas = 0;
///////////////////////////////////////////////
///////////DEEP_SLEEP/////////////////////////
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */

/////////////////////////////////////////////
/////////temperatura////////////////////////
const byte LED = 5;
/////////////////////////////////////webpage//////////////////
// Variable to store the HTTP request

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(27, INPUT_PULLUP); //Przycisk jako wejście


  Serial.println("normal mode");

  if (digitalRead(27) == LOW) {
    //wifirifi(); // wywołanie wifirifi
    init();
    MyOTA();
    Serial.println("Programing mode");
  }

}

float temp;
//float temp1;


void loop() {

  while (digitalRead(27) == LOW)
  {
    blink();
    //ArduinoOTA.handle();
    //temp_ds18b20(); // wywołanie odczytu czujnikow
    //sensors.requestTemperatures(); //Pobranie temperatury czujnika
    //temp1 = sensors.getTempCByIndex(0); // przypisanie pobranej temperatury
    //Serial.println("PRACA_TESTOWA");
    //Serial.println(temp1);
    //delay(500);


    //if (temp1 >= 23) {
          //Serial.println("OTWIERAM");
          //digitalWrite(LED, LOW); // to jest stan wysoki diody
          //digitalWrite(14, HIGH);
          //digitalWrite(12, LOW);
        //}


    //else {
        ////for (aktualnyCzas = millis(); millis() - aktualnyCzas < 10000UL) {
          //Serial.println("ZAMYKAM");
          //digitalWrite(LED, HIGH);
          //digitalWrite(14, LOW);
          //digitalWrite(12, HIGH);
        //}




    }

  Serial.println("DEEP_SLEEP"); // wchodzimy w deep sleep mode
///////////////////ważne//////////////////////////////////////
  //byte i;
  //for (i = 0; i < 3; i++) {
    //temp_ds18b20(); // wywołanie odczytu czujnikow
    //sensors.requestTemperatures(); //Pobranie temperatury czujnika
    //temp = sensors.getTempCByIndex(0); // przypisanie pobranej temperatury
    //Serial.print("temperatura : ");
    //Serial.println(temp);
    //delay(500); // musi byc 500 ms bo nie odczytuje prawidłowo inaczej
  //}



  //for(unsigned long x = millis(); millis() - x < 3;) {
  //blink();
  //}

// pobierz liczbe milisekund od startu

  //Jeśli różnica wynosi ponad 10 sekundę
  for (aktualnyCzas = millis(); millis() - aktualnyCzas < 10000UL;) {
    if (temp >= 25) {
      Serial.println("OTWIERAM");
      //Serial.println(temp);
      delay(500);
      digitalWrite(LED, LOW); // to jest stan wysoki diody
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
    }

    else if(temp <23) {
      Serial.println("ZAMYKAM");
      //Serial.println(temp);
      delay(500);
      digitalWrite(LED, HIGH);
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
    }
  }

  //for (aktualnyCzas = millis(); millis() - aktualnyCzas < 10000UL;) {
    //digitalWrite(LED, HIGH);
    //digitalWrite(12, LOW);
    //digitalWrite(14, HIGH);
    //Serial.println("OTWIERAM");
  //}


  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("ide spac!!");
  esp_deep_sleep_start();
}
