#include <ArduinoJson.h>


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        D3

#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Conexão Wi-Fi
  Serial.begin(115200);

  while (!Serial) {}

  # if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  # endif

  pixels.begin();
  
  delay(1000);

  lab_start();
}

void loop() {
  lab_loop();
}