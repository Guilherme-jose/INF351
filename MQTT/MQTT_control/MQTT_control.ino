#include <ArduinoMqttClient.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


char ssid[] = "Apto11"; 

char pass[] = "31415926"; 


WiFiClient wifiClient;

MqttClient mqttClient(wifiClient);


const char broker[] = "test.mosquitto.org";

int        port     = 1883;

const char topic[]  = "real_unique_topic";

const char topic2[]  = "real_unique_topic_2";

const char topic3[]  = "real_unique_topic_3";


void setup() {


  Serial.begin(115200);

  while (!Serial) {}

  Serial.print("Attempting to connect to SSID: ");

  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {

    Serial.print(".");

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


  mqttClient.onMessage(onMqttMessage);


  Serial.print("Subscribing to topic: ");

  Serial.println(topic);

  Serial.println();


  mqttClient.subscribe(topic);


  Serial.println();

}


void loop() {

   mqttClient.poll();


  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    int Rvalue = 'RIGHT'


    Serial.print("Sending message to topic: ");

    Serial.println(topic);

    Serial.println(Rvalue);


    mqttClient.beginMessage(topic);

    mqttClient.print(Rvalue);

    mqttClient.endMessage();


    Serial.println();

  }

}
