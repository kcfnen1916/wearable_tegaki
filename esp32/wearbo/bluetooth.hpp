#ifndef INCLUDE_GUARD_BLUETOOTH_HPP
#define INCLUDE_GUARD_BLUETOOTH_HPP

#include <BleKeyboard.h>
#include "BluetoothSerial.h"

//extern BleKeyboard bleKeyboard;
extern BluetoothSerial SerialBT;

void send_ble(String output);
#endif  // INCLUDE_GUARD_BLUETOOTH_HPP
