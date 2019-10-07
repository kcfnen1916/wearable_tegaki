from __future__ import print_function

import datetime
from datetime import timedelta
import os
import termios
from time import sleep
#シリアル通信の時は以下1行のコメントアウトをやめる
#import serial
import sys

def record_test():
  data = []
  wait_seconds = 300
  recording = False

  #シリアル通信の時は以下1行のコメントアウトをやめる
  #ser = serial.Serial('/dev/cu.usbserial-DN05JJRP', 115200, timeout=0)

  #シリアル通信の時は以下8行をコメントアウトする
  fd = sys.stdin.fileno()
  old = termios.tcgetattr(fd)
  new = termios.tcgetattr(fd)
  new[3] &= ~termios.ICANON
  new[3] &= ~termios.ECHO
  new[6][termios.VMIN] = 0  # cc
  new[6][termios.VTIME] = 0 # cc
  termios.tcsetattr(fd, termios.TCSANOW, new)

  flag = 0
  record = 0
  while 1:
    try:
      #シリアル通信の時は以下1行のコメントアウトをやめる
      #c = ser.read().decode('utf-8')
      #シリアル通信の時は以下1行をコメントアウトする
      key = sys.stdin.read(1)

      if key != '':
        if record == 0:
          record = 1
          start_time = datetime.datetime.now()
          last_now = start_time
        last_now = datetime.datetime.now()
        rec_time = (last_now - start_time).total_seconds() * 1000
        data.append((key,int(rec_time)))
    finally:
      now = datetime.datetime.now()
    if record == 0:
      last_now = now
    ep_time_from_last = (now-last_now).total_seconds() * 1000
    if abs(ep_time_from_last) > wait_seconds and start_time != last_now:
      break
  #シリアル通信の時は以下1行をコメントアウトする
  termios.tcsetattr(fd, termios.TCSANOW, old)
  #シリアル通信の時は以下1行のコメントアウトをやめる
  #ser.close()
  return (data,None)
