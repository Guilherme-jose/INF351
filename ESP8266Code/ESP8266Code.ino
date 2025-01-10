#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include "index.h" //MEMORY_TEST HTML

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        D3

#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "Labirinto";
const char* password = "12345678";


ESP8266WebServer server(80); //Server on port 80


void handleRoot() {
  String s = MAIN_page; //TO BE REPLACED WITH SPIFFS .html
  server.send(200, "text/html", s); //Send web page
}



void setup() {
  // Conexão Wi-Fi
  Serial.begin(115200);

  //while (!Serial) {}

  WiFi.softAP(ssid, password);
  Serial.println("Ponto de acesso criado!");
  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());

  // Configuração do servidor
  server.on("/", handleRoot);          // Página principal
  server.on("/up", up);                 // Botão de cima
  server.on("/down", down);             // Botão de baixo
  server.on("/left", left);             // Botão da esquerda
  server.on("/right", right);           // Botão da direita
  server.on("/releaseUp", releaseUp);   // Soltar botão de cima
  server.on("/releaseDown", releaseDown); // Soltar botão de baixo
  server.on("/releaseLeft", releaseLeft); // Soltar botão da esquerda
  server.on("/releaseRight", releaseRight); // Soltar botão da direita
  server.on("/a", a);                   // Botão A
  server.on("/b", b);                   // Botão B
  server.on("/releaseA", releaseA);     // Soltar botão A
  server.on("/releaseB", releaseB);     // Soltar botão B
  server.begin();
  Serial.println("Servidor iniciado.");
  

  # if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  # endif

  pixels.begin();

  lab_start();
}

void loop() {
  server.handleClient();
  
  lab_loop();
}
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 200;

void handleButtonPress(const String& button, bool pressed) {
  unsigned long currentTime = millis();
  if (currentTime - lastPressTime > debounceDelay) {
    lastPressTime = currentTime;
    if (pressed) {
      Serial.println(button + " button pressed");
      if (button == "left" || button == "right") {
        move(button);
      }
    } else {
      Serial.println(button + " button released");
    }
  }
}

void up() { handleButtonPress("Up", true); }
void down() { handleButtonPress("Down", true); }
void left() { handleButtonPress("left", true); }
void right() { handleButtonPress("right", true); }
void releaseUp() { handleButtonPress("Up", false); }
void releaseDown() { handleButtonPress("Down", false); }
void releaseLeft() { handleButtonPress("left", false); }
void releaseRight() { handleButtonPress("right", false); }
void a() { handleButtonPress("A", true); }
void b() { handleButtonPress("B", true); }
void releaseA() { handleButtonPress("A", false); }
void releaseB() { handleButtonPress("B", false); }
