//Code By Vermont Internet Design LLC, John Anderson 
// http://www.vermontinternetdesign.com
// Marshfield,VT 5/5/2018 info@vermontinternetdesign.com
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include "index.h" //MEMORY_TEST HTML


//SSID and Password of your WiFi router
const char* ssid = "VermontInternetDesign_asktouse";
const char* password = "Vermont1*";

ESP8266WebServer server(80); //Server on port 80
String bufferx;
int start = 0;
void handleRoot() {
 String s = MAIN_page; //TO BE REPLACED WITH SPIFFS .html
 server.send(200, "text/html", s); //Send web page
}
void HTML_setPin(){
      String t_pin = server.arg("PinNumber");
      String t_value = server.arg("HighLow");
      String t_ana = server.arg("IsAnalog");
      SendJSON(t_pin, t_value, t_ana, "0" );
      server.send(200, "text/plane", t_pin);
}
void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a); 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void SendJSON(String pin, String highlow, String ana, String respond){
     StaticJsonBuffer<200> jsonBuffer;
     JsonObject& root = jsonBuffer.createObject();
     root["IsAnalog"] = ana;
     root["Respond"] = respond;
     root["PinNumber"] = pin;
     root["HighLow"] = highlow;
     root.printTo(Serial);
}
void SendToHTML(String jsonii){
    

     server.send(200, "text/plane", jsonii);
     return;
}
void HTML_requestJSON(){
    String t_pin = server.arg("PinNumber");
    String t_ana = server.arg("IsAnalog");
    SendJSON(t_pin, "req", t_ana, "1"); 
    
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

void loop(void){
  server.handleClient();          //Handle client requests
  if (Serial.available()) {
         //Serial.println(mySerial.read());
            
           int incoming = Serial.read();
           if(incoming >= 32){
             //Serial.println(incoming);
             char character = (char) incoming;
           
             if(character == '{'){
                start = 1;
             }
             if(start == 1){
                bufferx.concat(character);
             }
             if(character == '}'){
              SendToHTML(bufferx);
              start = 0;
              bufferx = "";
             }
              
          }
  }
}
