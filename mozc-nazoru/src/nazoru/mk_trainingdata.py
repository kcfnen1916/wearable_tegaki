import datetime
from datetime import timedelta
import os
import termios
from time import sleep
# シリアル通信の時は以下1行のコメントアウトをやめる
#import serial
import sys
import ndjson

from keyboard_recorder import *

num_to_key_dic = {1: 't', 2: 'y', 3: 'u', 4: 'g', 5: 'h', 6: 'j', 7: 'b', 8: 'n', 9: 'm'}
#num_to_key_dic = {'1':'t','2':'y','3':'u','4':'g','5':'h','6':'j','7':'b','8':'n','9':'m'}


def num_to_key(num):
    return num_to_key_dic[num]


def mk_traindata(filename):

    output_list = []
    print("ラベルを入力してenterを押してください。")
    kana = sys.stdin.read(1)
    print("開始")
    c = 0
    try:
        while True:
            data, command = record()
            if len(data) == 1:
                continue
            else:
                c += 1
                data = list(map(lambda x: [x[0], x[1]], data))
                print(data)
                sys.stdout.write("{}回目の入力をしました。やめたい時はCtrl+Cを押してください。\n".format(c))
                list(map(lambda x: x.insert(1, 'down'), data))
                dic = {"kana": kana, "events": data}
                output_list.append(dic)
            if c % 10 == 0:
                with open(os.path.join('../../data/', filename), 'a') as f:
                    ndjson.dump(output_list, f)
                    f.write("\n")
                print("ここまでの入力を保存しました")
                output_list = []
    except KeyboardInterrupt:
        with open(os.path.join('../../data/', filename), 'a') as f:
            ndjson.dump(output_list, f)


if __name__ == '__main__':
    args = sys.argv
    if len(args) == 2:
        filename = args[1]
    else:
        filename = "strokes_mydata.ndjson"
    mk_traindata(filename)
