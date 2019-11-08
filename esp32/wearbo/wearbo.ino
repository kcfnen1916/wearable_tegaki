#include "bluetooth.hpp"
#include "flick.hpp"
#include "wifi.hpp"
//#include <WiFi.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    connectWiFi();

    Key testKey = Key(1, "test");
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("WiFi connected");
    } else {
        connectWiFi();
    }
    delay(1000);
}
