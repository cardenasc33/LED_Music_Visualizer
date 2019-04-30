#include <LiquidCrystal.h> 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //LCD Pins initialized


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char mystr[10];
String str;
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2); 
}

void loop() {
  //int sensorValue = Serial.read();
  //Serial.println(sensorValue);
  Serial.readBytes(mystr,10);
  //Serial.println(mystr);

  str = mystr;
  int val = str.toInt();
  
  displayLCD(val);

}

void displayLCD(int val) {

  lcd.setCursor(0, 0);
  Serial.println(val);
  int numLedsToLight = map(val, 0, 1023, 0, 255);
     
    if (numLedsToLight >= 200) {
      lcd.print("IT'S LIT");
    }
    else if(numLedsToLight >= 150) {
      lcd.print("Kinda lit");
    }
    else if(numLedsToLight >= 100) {
      lcd.print("Eh..");
    }
    else if(numLedsToLight >= 50) {
      lcd.print("Lame...");
    }
    
    
  
}