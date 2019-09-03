# -*- coding: utf-8 -*-
#
# Copyright 2018 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from __future__ import print_function

import datetime
from datetime import timedelta
import os
import termios
from time import sleep
# シリアル通信の時は以下1行のコメントアウトをやめる
#import serial
# mpr121
#import Adafruit_MPR121.MPR121 as MPR121
import sys

pin_to_key_dic = ['u', None, None, 'j', 'm', 'n', 'h', 'b', 'g', None, 't', 'y']
nottegaki_pin = [i for i in range(len(pin_to_key_dic)) if pin_to_key_dic[i] == None]

# socketの設定を書く クライアント
import socket
s=socket.socket (socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.43.27', 50000))


def record():
    data = []
    wait_seconds = 300
    recording = False

    # シリアル通信の時は以下1行のコメントアウトをやめる
    #ser = serial.Serial('/dev/cu.usbserial-DN05JJRP', 115200, timeout=0)

    # mpr121
    # cap = MPR121.MPR121()
    # if not cap.begin():
    #     print('Error initializing MPR121.  Check your wiring!')
    #     sys.exit(1)

    # シリアル通信の時は以下8行をコメントアウトする
    # fd = sys.stdin.fileno()
    # old = termios.tcgetattr(fd)
    # new = termios.tcgetattr(fd)
    # new[3] &= ~termios.ICANON
    # new[3] &= ~termios.ECHO
    # new[6][termios.VMIN] = 0  # cc
    # new[6][termios.VTIME] = 0  # cc
    # termios.tcsetattr(fd, termios.TCSANOW, new)

    flag = 0
    record = 0

    # mpr121
    #last_touched = cap.touched()
    #last_key = [0] * 12

    while 1:
        try:
            # シリアル通信の時は以下1行のコメントアウトをやめる
            #c = ser.read().decode('utf-8')
            # シリアル通信の時は以下1行をコメントアウトする
            key = s.recv(1024) # keyに送られてきた文字を入れるらしい
            print(key)
            #current_touched = cap.touched()
            if record == 0:
                record = 1
                start_time = datetime.datetime.now()
                last_now = start_time
            last_now = datetime.datetime.now()
            rec_time = (last_now - start_time).total_seconds() * 1000
            data.append((key, int(rec_time)))
            # for i in range(12):
            #     pin_bit = 1 << i
            #     if i in nottegaki_pin:
            #         continue
            #     if current_touched & pin_bit and not last_touched & pin_bit:
            #         last_now = datetime.datetime.now()
            #         rec_time = (last_now - start_time).total_seconds() * 1000
            #         if last_key[i] == 0:
            #             last_key[i] = 1
            #             data.append((pin_to_key_dic[i], int(rec_time)))
            #     if not current_touched & pin_bit and last_touched & pin_bit:
            #         last_key[i] = 0

        finally:
            now = datetime.datetime.now()
        if record == 0:
            last_now = now
        ep_time_from_last = (now - last_now).total_seconds() * 1000
        if abs(ep_time_from_last) > wait_seconds and start_time != last_now:
            break
    # シリアル通信の時は以下1行をコメントアウトする
    # termios.tcsetattr(fd, termios.TCSANOW, old)
    # シリアル通信の時は以下1行のコメントアウトをやめる
    s.close()
    return (data, None)
