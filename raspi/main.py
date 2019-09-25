import sys
import time
import datetime
from datetime import timedelta
import threading


import Adafruit_MPR121.MPR121 as MPR121
import serial

import gesture_config
from bluetooth import *


cap = MPR121.MPR121()

#ser = serial.Serial('/dev/cu.usbserial-DN05JJRP', 115200, timeout=0)

if not cap.begin():
    print('Error initializing MPR121.  Check your wiring!')
    sys.exit(1)
else:
    print('MPR121 initialized!')

bt_connection = Bluetooth()

wait_seconds = 300
recording = False

last_touched = cap.touched()
mode = gesture_config.mode

print('Press Ctrl-C to quit.')


def writing():
    while True:
        input_key_lst = []
        record = 0
        while True:
            current_touched = cap.touched()
            if record == 0:
                record = 1
                start_time = datetime.datetime.now()
                last_now = start_time
            try:
                for i in range(12):
                    pin_bit = 1 << i
                    if current_touched & pin_bit and not last_touched & pin_bit:
                        last_now = datetime.datetime.now()
                        rec_time = (last_now - start_time).total_seconds() * 1000
                        if not gesture_config.key_lst[i] in input_key_lst:
                            input_key_lst.append(gesture_config.key_lst[i])
            finally:
                now = datetime.datetime.now()
            ep_time_from_last = (now - last_now).total_seconds() * 1000
            if abs(ep_time_from_last) > wait_seconds and start_time != last_now:
                break
            last_touched = current_touched
        print(input_key_lst)
        # gesture判定
        if input_key_lst != []:
            for g in gesture_config.ges_lst:
                res, out = g.judge_gesture(input_key_lst)
                if res == 1 and out != None:
                    if not type(out) is bytes:
                        val = out.encode()
                    else:
                        val = out
                    bt_connection.send(val)
                    break


if __name__ == '__main__':
    writing()
