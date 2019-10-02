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

# この辺にsocketのimportとかを書く　サーバー
# ip=input()
import socket
args = sys.argv
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((args[1], 50000))
s.listen(1)
conn, addr = s.accept()

print('Press Ctrl-C to quit.')


def writing():
    while True:
        # 手書きモード
        if gesture_config.mode == 3:
            #print("Handwriting Mode")
            while True:
                input_key_lst = []
                record = 0
                hw_flag = True
                chr_list = []
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
                                if len(input_key_lst) == 0 and gesture_config.key_lst[i].chr == '-':
                                    hw_flag = False
                                if hw_flag:
                                    # シリアルで文字を送る
                                    if gesture_config.key_lst[i].chr != '-':
                                        chr_list.append(
                                            (gesture_config.key_lst[i].chr, str(int(rec_time))))
                                        # conn.send(gesture_config.key_lst[i].chr.encode()) # 文字を送っている、send
                                        print("Serial Write {}".format(
                                            gesture_config.key_lst[i].chr))
                                else:
                                    # 手書きではない時
                                    if not gesture_config.key_lst[i] in input_key_lst:
                                        input_key_lst.append(gesture_config.key_lst[i])
                    finally:
                        now = datetime.datetime.now()
                    ep_time_from_last = (now - last_now).total_seconds() * 1000
                    if abs(ep_time_from_last) > wait_seconds and start_time != last_now:
                        print(chr_list)
                        save = []
                        for i in range(len(chr_list)):
                            for j in range(2):
                                save.append(chr_list[i][j])
                        save = " ".join(save)
                        conn.send(save.encode())
                        break
                    last_touched = current_touched
                # gesture判定
                if not hw_flag and input_key_lst != []:
                    # print(input_key_lst)
                    for g in gesture_config.ges_lst[gesture_config.mode - 1]:
                        res, out = g.judge_gesture(input_key_lst)
                        if res == 1 and out != None:
                            if not type(out) is bytes:
                                val = out.encode()
                            else:
                                val = out
                            bt_connection.send(val)
                            break
                if gesture_config.mode != 3:
                    break
        # フリックモード
        elif gesture_config.mode == 1 or gesture_config.mode == 2:
            # if gesture_config.mode == 1:
                #print("Alphabet Flick Mode")
            # elif gesture_config.mode == 2:
                #print("Number Flick Mode")
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
                    for g in gesture_config.ges_lst[gesture_config.mode - 1]:
                        res, out = g.judge_gesture(input_key_lst)
                        if res == 1 and out != None:
                            if not type(out) is bytes:
                                val = out.encode()
                            else:
                                val = out
                            bt_connection.send(val)
                            break
                if gesture_config.mode == 3:
                    break


def receiving():
    while(1):
        data = conn.recv(1024)
        #data = data.decode()
        if data:
            print("receive:")
            print(data)
            bt_connection.send(data)


if __name__ == '__main__':
    t1 = threading.Thread(target=writing)
    t2 = threading.Thread(target=receiving)

    t1.start()
    t2.start()

s.close()
