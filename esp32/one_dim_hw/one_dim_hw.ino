#include "Arduino.h"
#include "bluetooth.hpp"
#include "one_dim_hw.hpp"
#include <M5StickC.h>

BleKeyboard bleKeyboard;

OneDimHW odhw = OneDimHW(12);

int vib_pin = 26;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting wearbo");

    odhw.m_cap = Adafruit_MPR121();

    if (!odhw.m_cap.begin(0x5A)) {
        Serial.println("MPR121 not found, check wiring?");
        while (1)
            ;
    }
    Serial.println("MPR121 found!");

    M5.begin();
    bleKeyboard.begin();

    Wire.begin(32, 33);

    pinMode(vib_pin, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
}
