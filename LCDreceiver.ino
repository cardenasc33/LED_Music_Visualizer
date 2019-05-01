//

/* Receiver portion of the code
  This code is responsible for the data being sent from the LED strip & Senssor from another arduino
 */

//Needed Library for the LCD
#include <LiquidCrystal.h> 

//Initializing pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //LCD Pins initialized
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Variables subject to change
char mystr[10]; //These specifically are for serial communication with another arduino
String str;
int val;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2); 
}

void loop() {
  if(Serial.available() > 0) {
    Serial.readBytes(mystr,4); //reading the data from the LED Strip arduino
    str = mystr; //turn the char array into a string
    val = str.toInt(); //change the string into a integer val to pass into displayLCD function
    displayLCD(val);
  }
}

void displayLCD(int val) {

  lcd.setCursor(0, 0); 
  
  Serial.println(val); //to keep track of frequency
  
  int numLedsToLight = map(val, 0, 1023, 0, 255);

     //based on the frequency/pitch it's receving from the sound sensor it'll display various messages on the LCD
    if (numLedsToLight >= 200) {
      lcd.clear();
      lcd.print("IT'S LIT");
      delay(2000);
    }
    else if(numLedsToLight >= 150) {
      lcd.clear();
      lcd.print("Okay!");
      delay(2000);
    }
    else if(numLedsToLight >= 100) {
      lcd.clear();
      lcd.print("Getting there");
      delay(2000);
    }
    else if(numLedsToLight >= 50) {
      lcd.clear();
      lcd.print("Lame");
      delay(2000);
    }
       
    
  
}
