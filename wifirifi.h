#include "Arduino.h"

#include <WiFi.h>        // Include the Wi-Fi library




//WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti

//const char *ssid = "DWR-116_E45A4A"; // The name of the Wi-Fi network that will be created
//const char *password = "polanczyk77";   // The password required to connect to it, leave blank for an open network
const char *ssid = "ESP-32_koval";
const char *password = "polanczyk77";

WiFiServer server(80);


void wifirifi() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
  server.begin(); // start server

  // wifi client Start // wifi client Start // wifi client Start
  // wifi client Start // wifi client Start // wifi client Start
  // wifi client Start // wifi client Start // wifi client Start

  //Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  //delay(10);
  //Serial.println('\n');

  //WiFi.begin(ssid, password);             // Connect to the network
  //Serial.print("Connecting to ");
  //Serial.print(ssid); Serial.println(" ...");

  //int i = 0;
  //while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    //delay(1000);
    //Serial.print(++i); Serial.print(' ');
  //}

//  Serial.println('\n');
  //Serial.println("Connection established!");
  //Serial.print("IP address:\t");
  //Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}
