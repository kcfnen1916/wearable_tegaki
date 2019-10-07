#!/usr/bin/env python
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

# Surpress warnings. Please unvail these warnings when development.
import warnings
warnings.filterwarnings("ignore", category=RuntimeWarning)
warnings.filterwarnings("ignore", category=FutureWarning)

import time

import argparse
import os
import unicodedata
import sys
import ndjson

CWD_PATH = os.getcwd()
src_path = os.path.join('/'.join(sys.path[0].split('/')[:-1]), 'src')
sys.path.append(src_path)

#from nazoru.keyboard_recorder import record
from nazoru.keyboard_recorder_test import record_test

from nazoru.core_train import *

def get_default_graph_path():
  return os.path.join(src_path,'nazoru/data/optimized_nazoru.pb')

def main():
    FLAGS = None
    parser = argparse.ArgumentParser()
    parser.add_argument('-g', '--graph',
                      type=str,
                      default=get_default_graph_path(),
                      help='Path to a trained model which is generated by ' +
                           'nazoru-training.')
    parser.add_argument('-v', '--verbose', action='store_true')
    FLAGS, unparsed = parser.parse_known_args()
    predictor = NazoruPredictor(FLAGS.graph)
    print('Ready. Please scrrible on your keyboard.')
    with open('../data/sanodata.ndjson') as f:
        data = ndjson.load(f)
    c = 0
    k = 0
    for d in data:
        k += 1
        command = None
        kana = d["kana"]
        print(d["events"])
        input = []
        for i in range(len(d["events"])):
            input.append((d["events"][i][0],d["events"][i][2]))
        if command is not None:
            print('command: %s' % command)
            continue
        if d is None:
            print('done.')
            break
        try:
            result,img = predictor.predict_top_n(input, 5)
            print(img[0,:,:,8].shape)
            X_im_8 = img[0,:,:,8]*500
            X_im_9 = img[0,:,:,9]*500
            print(X_im_9)
            pil_img_f_8 = Image.fromarray(X_im_8.astype(np.uint8))
            pil_img_f_9 = Image.fromarray(X_im_9.astype(np.uint8))
            pil_img_f_8.save('./images/{}_{}_usuku.png'.format(k,kana))
            pil_img_f_9.save('./images/{}_{}_koku.png'.format(k,kana))
        except IndexError:
        # This is possible when pressing keys we don't use for learning.
            print('Invalid input. (out of range)')
            continue
        except ValueError:
      # This is possible when pressing only one key.
            print('Invalid input. (one key)')
            continue

        clear_screen()
        print('\n===== RESULTS =====')
        for item in result:
            if unicodedata.east_asian_width(item[0]) in {'W', 'F'}:
                surface = item[0]
            else:
                surface = item[0] + ' '
        print(u'%s (%4s): %.5f' % (surface, item[1], item[2]))
        print('===================\n')

        most_likely_result = result[0]
        print(u'prediction: %s (%s)' % (most_likely_result[0], most_likely_result[1]))
        print(most_likely_result[0] == kana)
        if most_likely_result[0] == kana:
            c+=1
    print("precision : {}%".format(c/len(data)*100))
    #client.send(most_likely_result[0].encode())

if __name__ == '__main__':
  main()


