#include <M5StickC.h>

int PIN = 26;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  M5.begin();
 
  pinMode(PIN, OUTPUT);
}

void loop()
{
  for ( int val = 0; val < 255; val += 20 ) {
    if(val==0){
      M5.Lcd.print("Hello World");
    }
    dacWrite( PIN, val );
    delay( 300 );
  }

}
  
