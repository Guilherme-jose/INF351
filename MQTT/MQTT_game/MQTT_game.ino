#include <ArduinoMqttClient.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char ssid[] = "Apto11"; 

char pass[] = "31415926";


WiFiClient wifiClient;

MqttClient mqttClient(wifiClient);


const char broker[] = "test.mosquitto.org";

int        port     = 1883;

const char topic[]  = "UFV_JOGO_LABIRINTO";


const long interval = 8000;

unsigned long previousMillis = 0;


int count = 0;


void setup() {
  Serial.begin(9600);

  while (!Serial) {}

  Serial.print("Attempting to connect to SSID: ");

  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {

    Serial.println(".");

    delay(5000);

  }


  Serial.println("You're connected to the network");

  Serial.println();


  Serial.print("Attempting to connect to the MQTT broker: ");

  Serial.println(broker);


  if (!mqttClient.connect(broker, port)) {

    Serial.print("MQTT connection failed! Error code = ");

    Serial.println(mqttClient.connectError());


    while (1);

  }


  Serial.println("You're connected to the MQTT broker!");

  Serial.println();

}


void loop() {

  mqttClient.poll();

}



void onMqttMessage(int messageSize) {

  // we received a message, print out the topic and contents

  Serial.println("Received a message with topic '");

  Serial.print(mqttClient.messageTopic());

  Serial.print("', length ");

  Serial.print(messageSize);

  Serial.println(" bytes:");


  // use the Stream interface to print the contents

  while (mqttClient.available()) {

    Serial.print((char)mqttClient.read());

  }

  Serial.println();

  Serial.println();

}