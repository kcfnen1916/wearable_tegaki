#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
}
void loop() {
  if (bleKeyboard.isConnected()) {
    bleKeyboard.print("Hello world");
    bleKeyboard.write(KEY_RETURN);
  }
  delay(5000);
}
