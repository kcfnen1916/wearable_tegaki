#include "bluetooth.hpp"
#include "Arduino.h"
#include "BluetoothSerial.h"


void send_ble(String output)
{
    Serial.println(output);
    if (output == "ENTER") {
        bleKeyboard.write(KEY_RETURN);
    } else if (output == "BACKSPACE") {
        bleKeyboard.write(KEY_BACKSPACE);
    } else if (output == "LEFT") {
        bleKeyboard.write(KEY_LEFT_ARROW);
    } else if (output == "RIGHT") {
        bleKeyboard.write(KEY_RIGHT_ARROW);
    } else if (output == "SPACE"){
       bleKeyboard.print(" ");
    } else if (output == "tweet"){
      
    } else {
        bleKeyboard.print(output);
    }
}
