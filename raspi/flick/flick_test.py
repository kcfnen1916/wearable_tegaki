import sys
import time
import datetime
from datetime import timedelta

import Adafruit_MPR121.MPR121 as MPR121

from flick import *
import gesture_config


print('Adafruit MPR121 Capacitive Touch Sensor Test')

cap = MPR121.MPR121()

if not cap.begin():
    print('Error initializing MPR121.  Check your wiring!')
    sys.exit(1)

wait_seconds = 300
recording = False


print('Press Ctrl-C to quit.')
last_touched = cap.touched()
while True:
    input_key_lst = []
    record = 0
    print("Input Start")
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
        for g in gesture_config.ges_lst[gesture_config.mode - 1]:
            res = g.judge_gesture(input_key_lst)
            if res == 1:
                break

# test
# input_key_lst = [gesture_config.cul, gesture_config.klmn, gesture_config.opqrs,
#                  gesture_config.tuvw, gesture_config.space]
# print(input_key_lst)
# print(gesture_config.mode)
# if input_key_lst != []:
#     for g in gesture_config.ges_lst[gesture_config.mode - 1]:
#         res = g.judge_gesture(input_key_lst)
#         if res == 1:
#             print("Gesture Found")
#             break
# print(gesture_config.mode)
