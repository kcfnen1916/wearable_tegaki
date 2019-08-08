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

# from __future__ import print_function
#
# import datetime
# from datetime import timedelta
# import os
# import serial
#
# def record():
#   wait_seconds = 1000
#   recording = False
#   while True:
#     ser = serial.Serial('/dev/cu.usbserial-DN05JJRP', 115200, timeout=1)
#     data = []
#     while True:
#       c = ser.read().decode('utf-8')
#       now = datetime.datetime.now()
#       if not recording:
#         recording = True
#         start_time = datetime.datetime.now()
#       ep_time_ms = int((now-start_time).total_seconds() * 1000)
#       last_time = now
#       if last_time and ep_time_ms > wait_seconds:
#         break
#       if c == '':
#         continue
#       else:
#         data.append((c,ep_time_ms))
#     ser.close
#     if len(data) != 1:
#       break
#   return (data,None)
