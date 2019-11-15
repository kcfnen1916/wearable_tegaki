#include "bluetooth.hpp"
#include "config.hpp"
#include "flick.hpp"
#include "wifi.hpp"
#include <M5StickC.h>


void setup()
{
    Serial.begin(115200);
    Serial.println("Starting wearbo");

    M5.begin();

    connectWiFi();
    setup_client();

    xTaskCreatePinnedToCore(task_main, "Task_main", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(task_recv, "Task_recv", 4096, NULL, 2, NULL, 1);
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("WiFi connected");
    } else {
        connectWiFi();
    }
}


void task_main(void* arg)
{
    wearbo.main();
}

void task_recv(void* arg)
{
    wearbo.receive_hwd();
}
