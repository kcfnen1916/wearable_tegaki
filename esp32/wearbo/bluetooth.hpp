#ifndef INCLUDE_GUARD_MOTOR_HPP
#define INCLUDE_GUARD_MOTOR_HPP

#include "Arduino.h"
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDKeyboardTypes.h"
#include "HIDTypes.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <driver/adc.h>

extern BLEHIDDevice* hid;
extern BLECharacteristic* input;
extern BLECharacteristic* output;

extern uint8_t buttons;
extern uint8_t button1;
extern uint8_t button2;
extern uint8_t button3;
extern bool connected;

class MyCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
};

/*
 * This callback is connect with output report. In keyboard output report report special keys changes, like CAPSLOCK, NUMLOCK
 * We can add digital pins with LED to show status
 * bit 0 - NUM LOCK
 * bit 1 - CAPS LOCK
 * bit 2 - SCROLL LOCK
 */
class MyOutputCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic* me);
};

void taskServer(void*);


IRAM_ATTR void clickNumLock();
IRAM_ATTR void clickCapsLock();
IRAM_ATTR void clickScrollLock();

#endif  // INCLUDE_GUARD_MOTOR_HPP
