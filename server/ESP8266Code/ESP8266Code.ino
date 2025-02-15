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

bool leftPressed = false;
bool rightPressed = false;
bool upPressed = false;
bool downPressed = false;
bool aPressed = false;
bool bPressed = false;


void setup() {
  // Conexão Wi-Fi
  Serial.begin(115200);

  while (!Serial) {}

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
  server.on("/a", a);                   // Botão A
  server.on("/b", b);                   // Botão B
  server.on("/stop", stop);     // Soltar botão A
  server.begin();
  Serial.println("Servidor iniciado.");
  

  # if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  # endif

  pixels.begin();
  
  delay(1000);

  lab_start();
}

void loop() {
  server.handleClient();
  if (leftPressed) {
    move("left");
  } else if (rightPressed) {
    move("right");
  } else if (upPressed) {
    move("up");
  } else if (downPressed) {
    move("down");
  } else if (aPressed) {
    move("a");
  } else if (bPressed) {
    move("b");
  }
  lab_loop();
  delay(200);
}



void handleButtonPress(const String& button, bool pressed) {
  if (pressed) {
    if (button == "up") {
      upPressed = true;
    } else if (button == "down") {
      downPressed = true;
    } else if (button == "left") {
      leftPressed = true;
    } else if (button == "right") {
      rightPressed = true;
    } else if (button == "A") {
      aPressed = true;
    } else if (button == "B") {
      bPressed = true;
    } else if (button == "stop") {
      leftPressed = false;
      rightPressed = false;
      upPressed = false;
      downPressed = false;
      aPressed = false;
      bPressed = false;
    }
    Serial.println(button + " button pressed");
  } else {
    Serial.println(button + " button released");
  }
  server.send(200, "text/plain", "OK");
}

void up() { handleButtonPress("up", true); }
void down() { handleButtonPress("down", true); }
void left() { handleButtonPress("left", true); }
void right() { handleButtonPress("right", true); }
void a() { handleButtonPress("A", true); }
void b() { handleButtonPress("B", true); }
void stop() { handleButtonPress("stop", true); }
