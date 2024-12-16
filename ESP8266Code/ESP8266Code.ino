#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include "index.h" //MEMORY_TEST HTML

const char* ssid = "VermontInternetDesign_asktouse";
const char* password = "Vermont1*";


ESP8266WebServer server(80); //Server on port 80
String bufferx;
int start = 0;
void handleRoot() {
  String s = MAIN_page; //TO BE REPLACED WITH SPIFFS .html
  server.send(200, "text/html", s); //Send web page
}


void setup(void){
  Serial.begin(9600);
  while (!Serial) continue;
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
   Serial.println(WiFi.localIP());
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/SetPin", HTML_setPin);
  server.on("/GetJSON", HTML_requestJSON);
  server.begin(); 
}