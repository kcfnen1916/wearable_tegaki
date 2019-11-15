#include "bluetooth.hpp"
#include "config.hpp"
#include "flick.hpp"
#include "wifi.hpp"
//#include <WiFi.h>
// void ArrayOut(int AccData[])
// {
//     for (int i = 0; i < sizeof(AccData) + 1; i++) {
//         Serial.println(AccData[i]);
//     }
// }
void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE work!");

    connectWiFi();
    int myData[] = {1, 2, 3, 4, 5};
    // ArrayOut(myData);
    // Key testKey = Key(1, "test");
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
