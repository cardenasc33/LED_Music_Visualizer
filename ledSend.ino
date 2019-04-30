// code snippet used from https://forum.arduino.cc/index.php?topic=433725.0
#include "FastLED.h"
#include <LiquidCrystal.h>

#define NUM_LEDS 300 // Number of LEDS in the strip
#define DATA_PIN 6
#define SCROLL_SPEED 15

CRGB leds[NUM_LEDS];

const int sensorPin = A0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //LCD Pins initialized
int count = 0;
unsigned long lastUpdate;
int sensorValue;
char valueChar[5];
char mystr[5] = "Hello";
String str;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  lcd.begin(16,2);
  pinMode(sensorPin, INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue == 0) return;

  //Serial.write(mystr,5); 
  //delay(1000);
  str = String(sensorValue);
  //Serial.write(str);
  
  str.toCharArray(valueChar, 5);  
  Serial.write(valueChar);
  //Serial.write(sensorValue);
  
  
  Serial.print("\n");
  lightUp(sensorValue);
  
  
  displayLCD(sensorValue);
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

void displayLCD(int val) {

  lcd.setCursor(0, 0);
  
  
  while(Serial.available() > 0) {
    
    if (Serial.read() >= 200) {
      lcd.print("IT'S LIT");
    }
    else if(Serial.read() >= 150) {
      lcd.print("Kinda lit");
    }
    else if(Serial.read() >= 100) {
      lcd.print("Eh..");
    }
    else if(Serial.read() >= 50) {
      lcd.print("Lame...");
    }
    
  }
  
}
