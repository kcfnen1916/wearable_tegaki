#include "bluetooth.hpp"
#include "flich.hpp"

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    pinMode(12, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(12), clickNumLock, CHANGE);  // Num Lock
    pinMode(14, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(13), clickCapsLock, CHANGE);  // Caps Lock
    pinMode(32, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(32), clickScrollLock, CHANGE);  // Scroll Lock

    xTaskCreate(taskServer, "server", 20000, NULL, 5, NULL);
}

void loop()
{

    if (connected) {

        vTaskDelay(1);
        uint8_t str = 1;
        if (Serial.available() > 0) {
            // 受信したデータの1バイトを読み取る
            char inputbyte = Serial.read();
            str = (uint8_t)inputbyte;

            KEYMAP map = keymap[str];
            Serial.println(str);
            uint8_t msg[] = {map.modifier || buttons, 0x0, map.usage, 0x0, 0x0, 0x0, 0x0, 0x0};
            input->setValue(msg, sizeof(msg));
            input->notify();
            uint8_t msg1[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

            input->setValue(msg1, sizeof(msg1));
            input->notify();
        }
    }
    delay(50);
}
