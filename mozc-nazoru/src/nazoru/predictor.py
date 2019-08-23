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

from __future__ import absolute_import

import tensorflow as tf
from .lib import *
from .utils import *
import numpy as np

def _load_graph(model_file): #model_fileは学習済みモデル
  graph = tf.Graph()
  graph_def = tf.GraphDef()
  with open(model_file, "rb") as f:
    graph_def.ParseFromString(f.read())
  with graph.as_default():
    tf.import_graph_def(graph_def)
  return graph

class NazoruPredictor():
  def __init__(self, model_file):
    graph = _load_graph(model_file)#学習済みモデルを読み込む
    self._graph = graph
    self._input_operation = graph.get_operation_by_name(
        'import/' + INPUT_NODE_NAME)
    self._output_operation = graph.get_operation_by_name(
        'import/' + OUTPUT_NODE_NAME)

  def _predict(self, data):
    with Measure('inputs'):
      inputs = keydowns2image(data, True, True, 16, 2)#inputを読み込む
      inputs = np.expand_dims(inputs, axis=0)
    with Measure('sess.run'):
      with tf.Session(graph=self._graph) as sess:
        result = sess.run(self._output_operation.outputs[0],
                          {self._input_operation.outputs[0]: inputs})[0]
    return result
  def predict_top_n(self, data, n):
    """Predict the charactor drawn by |data|.

    Args:
      data: [(key, time)] |time| is elapsed time since the first character in ms.
      n: integer of the number of the return value.
    Returns:
      ans: [(kana, key, probability)] sorted by the probability.
    """
    result = self._predict(data)
    ans = []
    for i in result.argsort()[::-1][:n]:
      ans.append((KANAS[i], KEYS[i], result[i]))
    return ans