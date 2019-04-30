#include "IRremote.h"
#include "Wire.h"

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
int prev = 0;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  
  if (irrecv.decode(&results)) {
      Serial.println(results.value);
        if (results.value == 16753245) {
          if (prev == 1) {
            Wire.beginTransmission(9);
            Wire.write('E');
            Wire.endTransmission();
            prev = 0;
          }
          else {
            Wire.beginTransmission(9);
            Wire.write('S');
            Wire.endTransmission();
            prev = 1;
          }
        }     
        irrecv.resume();
  }
}
