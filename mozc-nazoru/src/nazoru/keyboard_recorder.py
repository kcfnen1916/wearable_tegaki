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
 #import serial
import sys

def record():
  data = []
  wait_seconds = 300
  recording = False

  #ser = serial.Serial('/dev/cu.usbserial-DN05JJRP', 115200, timeout=1)

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
    """
    if record == 0:
      record = 1
      start_time = datetime.datetime.now()
      last_now = start_time
    """
    try:
      #c = ser.read().decode('utf-8')
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
  termios.tcsetattr(fd, termios.TCSANOW, old)
  return (data,None)


