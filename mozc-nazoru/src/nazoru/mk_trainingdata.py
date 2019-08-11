import datetime
from datetime import timedelta
import os
import termios
from time import sleep
#シリアル通信の時は以下1行のコメントアウトをやめる
#import serial
import sys
import ndjson

from keyboard_recorder import *

def mk_traindata(filename):

    output_list = []
    print("ラベルを入力してenterを押してください。")
    kana = sys.stdin.read(1)
    print("開始")
    c = 1
    while True:
        data, command = record()
        if len(data) == 1 and c == 1:
            continue
        elif data == [('q',0)]:
            print("終了します")
            break
        else:
            sys.stdout.write("{}回目の入力をしました。やめたい時はqを押してください。(enterは押さないで！)\n".format(c))
            c += 1
            data = list(map(lambda x: list(x), data))
            list(map(lambda x: x.insert(1,'down'), data))
            dic = {"kana" : kana, "events" : data}
            output_list.append(dic)
    with open(os.path.join('../../data/', filename), 'a') as f:
        ndjson.dump(output_list, f)


args = sys.argv
if len(args) == 2:
     filename = args[1]
else:
    filename = "strokes_mydata.ndjson"
mk_traindata(filename)