#include "wifi.h"

const char ssid[] = "techgarage-guest";
const char passwd[] = "deployordie";

void connectWiFi()
{
    WiFi.begin(ssid, passwd);
    Serial.print("WiFi connecting...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.print(" connected. ");
    Serial.println(WiFi.localIP());
}
