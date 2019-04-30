// code snippet used from https://forum.arduino.cc/index.php?topic=433725.0
#include "FastLED.h"
#include <LiquidCrystal.h>
#include "Wire.h"

#define NUM_LEDS 300 // Number of LEDS in the strip
#define DATA_PIN 6
#define SCROLL_SPEED 15

CRGB leds[NUM_LEDS];

const int sensorPin = A0;
unsigned long lastUpdate;
int sensorValue;
char str[4];
int x; // stores the byte from i2c connection

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin(9);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  lcd.begin(16,2);
  pinMode(sensorPin, INPUT);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
  x = Wire.read();
}

void loop() {
  if (x == 'S') {
    sensorValue = analogRead(sensorPin);
    if (sensorValue == 0) return;
    itoa(sensorValue, str, 10);
    Serial.write(str, 4);  
    
    Serial.print("\n");
    lightUp(sensorValue);
  }
  else if (x == 'E') {
  }
}

void lightUp(int val) {
  int numLedsToLight = map(val, 0, 1023, 0, 255);
    if (numLedsToLight >= 200) {
      leds[0] = CRGB:: Violet;
      leds[1] = CRGB:: Violet;
      leds[2] = CRGB:: Violet;
    }
    else if(numLedsToLight >= 150) {
      leds[0] = CRGB:: Cyan;
      leds[1] = CRGB:: Cyan;
      leds[2] = CRGB:: Cyan;
    }
    else if(numLedsToLight >= 100) {
      leds[0] = CRGB:: Red;
      leds[1] = CRGB:: Red;
      leds[2] = CRGB:: Red;
      
    }
    else if(numLedsToLight >= 50) {
      leds[0] = CRGB:: Green;
      leds[1] = CRGB:: Green;
      leds[2] = CRGB:: Green;
    }
    else
      leds[0] = CRGB::Black;
      
    if (millis() - lastUpdate > SCROLL_SPEED) {
      lastUpdate += SCROLL_SPEED;
      for (int i = NUM_LEDS - 1; i > 0; i--)
        leds[i] = leds[i - 1];
      FastLED.show();
    }
  }
