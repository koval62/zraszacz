
#include "Arduino.h"
#include "temp_ds18b20.h"
//#include <WiFi.h>
//#include "wifirifi.h"

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP-32_koval";
const char* password = "polanczyk77";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;


// Auxiliar variables to store the current output state
String water = "close";
//String output13State = "on";

// Assign output variables to GPIO pins
const int otworz = 12;
const int zamknij = 13;
const int test = 5; // zmienna do testow (LED)

void init() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(otworz, OUTPUT);
  pinMode(zamknij, OUTPUT);
  pinMode(test, OUTPUT);
  // Set outputs to LOW
  digitalWrite(otworz, HIGH);
  digitalWrite(zamknij, LOW);
  digitalWrite(test,HIGH);

  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
  server.begin(); // start server

}


void blink(){


  ////////////////////////server//////////////////
    //pinMode(output26, OUTPUT);
    //pinMode(output27, OUTPUT);
    // Set outputs to LOW
    //digitalWrite(output26, LOW);
    //digitalWrite(output27, LOW);


  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port

    byte i;
    for (i = 0; i < 3; i++) {
    readTemp(); //proba nie strzelba
    }

    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:

          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("woda otwarta");
              water = "open";
              //digitalWrite(open, HIGH);
              //digitalWrite(close, LOW);
              digitalWrite(5, LOW);
            }

            if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("water close");
              water = "close";
              digitalWrite(5, HIGH);

          //  } else if (header.indexOf("GET /13/on") >= 0) {
          //    Serial.println("GPIO 13 on");
          //    output13State = "on";
          //    digitalWrite(output13, HIGH);
            //  digitalWrite(output12, LOW);

          //  } else if (header.indexOf("GET /13/off") >= 0) {
          //    Serial.println("GPIO 13 off");
          //    output13State = "off";
            //  digitalWrite(output13, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");

            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>pizdjet_server</h1>");

            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>STATE : " + water + "</p>");
            // If the output26State is off, it displays the ON button
            if (water=="close") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">OPEN</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">CLOSE</button></a></p>");
            }
            ////////////////////////temperatura////////////////////
            client.println("<h3>Temperature in Celsius: ");
            client.println(temp1,1);

            // Display current state, and ON/OFF buttons for GPIO 27
          //  client.println("<p>GPIO 13 - State " + output13State + "</p>");
            // If the output27State is off, it displays the ON button
          //  if (output13State=="off") {
          //    client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
          //  } else {
          //    client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
        //    }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
