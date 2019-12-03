// #include "wifi.h"
//
// const char ssid[] = "techgarage-guest";
// const char passwd[] = "deployordie";
//
// const char* host = "iot.hongo.wide.ad.jp";
// const int port = 30005;
//
// WiFiClient client;
//
// void connectWiFi()
// {
//     WiFi.begin(ssid, passwd);
//     Serial.print("WiFi connecting...");
//     while (WiFi.status() != WL_CONNECTED) {
//         Serial.print(".");
//         delay(100);
//     }
//     Serial.print(" connected. ");
//     Serial.println(WiFi.localIP());
// }
//
// void setup_client()
// {
//     client.connect(host, port);
// }
