#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
int res[20];
char key[12] = {'i','k','m','j','u','7','y','n','h','b','g','t'};
char pressed_key;
char last_pressed_key;

void setup() {
  Serial.begin(115200);
  delay(1000); //シリアル通信準備待ち時間
  //Serial.println("ESP32 Touch Test with MPR121");
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    //Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  //Serial.println("MPR121 found!");

  for (uint8_t i = 0; i < 20; i++) {
    res[i] = 0;
  }

}

void get_esptouch(int id, int sen_out){
  if(sen_out < 23){
    res[id] = 1;
   }else{
    res[id] = 0;
  }
}

void loop() {
  
  // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, send the keyname!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      pressed_key = key[i];
      if (last_pressed_key != pressed_key){
        Serial.print(pressed_key);
      }
    }
  }

  // reset our state
  lasttouched = currtouched;
  last_pressed_key = pressed_key;

}
