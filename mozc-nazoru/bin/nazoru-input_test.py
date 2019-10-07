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
  k = 0
  while True:
    k += 1
    data, command = record_test()
    print(data)
    if command is not None:
      print('command: %s' % command)
      continue
    if data is None:
      print('done.')
      break
    try:
      result,img = predictor.predict_top_n(data, 5)
      print(img[0,:,:,8].shape)
      X_im_1 = img[0,:,:,0]*100
      X_im_2 = img[0,:,:,1]*100
      X_im_3 = img[0,:,:,2]*100
      X_im_4 = img[0,:,:,3]*100
      X_im_5 = img[0,:,:,4]*100
      X_im_6 = img[0,:,:,5]*100
      X_im_7 = img[0,:,:,6]*100
      X_im_8 = img[0,:,:,7]*100
      X_im_9 = img[0,:,:,8]*100
      X_im_10 = img[0,:,:,9]*100
      kana = "test"
      pil_img_f_8 = Image.fromarray(X_im_8.astype(np.uint8))
      pil_img_f_9 = Image.fromarray(X_im_9.astype(np.uint8))
      pil_img_f_8.save('./images/{}_{}_8.png'.format(k,kana))
      pil_img_f_9.save('./images/{}_{}_usuku.png'.format(k,kana))
      pil_img_f_1 = Image.fromarray(X_im_1.astype(np.uint8))
      pil_img_f_2 = Image.fromarray(X_im_2.astype(np.uint8))
      pil_img_f_1.save('./images/{}_{}_1.png'.format(k,kana))
      pil_img_f_2.save('./images/{}_{}_2.png'.format(k,kana))
      pil_img_f_3 = Image.fromarray(X_im_3.astype(np.uint8))
      pil_img_f_4 = Image.fromarray(X_im_4.astype(np.uint8))
      pil_img_f_3.save('./images/{}_{}_3.png'.format(k,kana))
      pil_img_f_4.save('./images/{}_{}_4.png'.format(k,kana))
      pil_img_f_5 = Image.fromarray(X_im_5.astype(np.uint8))
      pil_img_f_6 = Image.fromarray(X_im_6.astype(np.uint8))
      pil_img_f_5.save('./images/{}_{}_5.png'.format(k,kana))
      pil_img_f_6.save('./images/{}_{}_6.png'.format(k,kana))
      pil_img_f_7 = Image.fromarray(X_im_7.astype(np.uint8))
      pil_img_f_10 = Image.fromarray(X_im_8.astype(np.uint8))
      pil_img_f_7.save('./images/{}_{}_7.png'.format(k,kana))
      pil_img_f_10.save('./images/{}_{}_koku.png'.format(k,kana))
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
    print(u'prediction: %s (%s)' % (
      most_likely_result[0], most_likely_result[1]))

    #client.send(most_likely_result[0].encode())

if __name__ == '__main__':
  main()


