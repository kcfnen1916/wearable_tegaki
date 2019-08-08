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
import sys
import time


import Adafruit_MPR121.MPR121 as MPR121


def record():
    cap = MPR121.MPR121()
    wait_seconds = 1000
    recording = False
    key_lst = ['i', 'k', 'm', 'j', 'u', '7', 'y', 'n', 'h', 'b', 'g', 't']
    last_key = ''
    if not cap.begin():
        print('Error initializing MPR121.  Check your wiring!')
        sys.exit(1)
    last_touched = cap.touched()
    while True:
        data = []
        while True:
            current_touched = cap.touched()
            for i in range(12):
                pin_bit = 1 << i
                if current_touched & pin_bit and not last_touched & pin_bit:
                    if last_key != key_lst[i]:
                        c = key_lst[i]
            last_touched = current_touched
            now = datetime.datetime.now()
            if not recording:
                recording = True
                start_time = datetime.datetime.now()
            ep_time_ms = int((now - start_time).total_seconds() * 1000)
            last_time = now
            if last_time and ep_time_ms > wait_seconds:
                break
            if c == '':
                continue
            else:
                data.append((c, ep_time_ms))
        if len(data) != 1:
            break
    return (data, None)
