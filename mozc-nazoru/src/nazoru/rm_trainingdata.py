import ndjson
import sys


data_dic = {}
BOTTOM_RIGHT = ['h', 'j', 'n', 'm']
BOTTOM_LEFT = ['g', 'h', 'b', 'n']
UPPER_RIGHT = ['h', 'j', 'y', 'u']
UPPER_LEFT = ['t', 'y', 'g', 'h']
BOTTOM_LINE = ['t', 'y', 'u']
UPPER_LINE = ['b', 'n', 'm']
EVERYWHERE = ['t', 'y', 'u', 'g', 'h', 'j', 'b', 'n', 'm']


class Data:

    def __init__(self, label, max_in, min_in, start, finish):
        self.m_label = label
        self.m_max_in = max_in
        self.m_min_in = min_in
        self.m_start = start
        self.m_finish = finish
        data_dic[label] = self


a = Data('a', 20, 5, UPPER_RIGHT, BOTTOM_RIGHT)
b = Data('b', 17, 3, UPPER_LEFT, BOTTOM_LEFT)
c = Data('c', 15, 4, UPPER_RIGHT, BOTTOM_RIGHT)
d = Data('d', 17, 3, UPPER_RIGHT, BOTTOM_RIGHT)
e = Data('e', 15, 3, ['g', 'h'], BOTTOM_RIGHT)
f = Data('f', 15, 4, UPPER_RIGHT, ['u', 'j', 'm', 'h'])
g = Data('g', 20, 3, UPPER_RIGHT, BOTTOM_LEFT)
h = Data('h', 20, 3, UPPER_LEFT, BOTTOM_RIGHT)
i = Data('i', 10, 3, EVERYWHERE, BOTTOM_RIGHT)
j = Data('j', 10, 3, EVERYWHERE, BOTTOM_RIGHT)
k = Data('k', 15, 3, UPPER_LEFT, BOTTOM_RIGHT)
l = Data('l', 15, 3, EVERYWHERE, BOTTOM_LINE)
m = Data('m', 20, 5, UPPER_LEFT, BOTTOM_RIGHT)
n = Data('n', 15, 3, UPPER_LEFT, BOTTOM_RIGHT)
o = Data('o', 15, 3, EVERYWHERE, EVERYWHERE)
p = Data('p', 15, 3, UPPER_LEFT, BOTTOM_LEFT)
q = Data('q', 15, 3, UPPER_RIGHT, BOTTOM_RIGHT)
r = Data('r', 15, 3, UPPER_LEFT, UPPER_RIGHT)
s = Data('s', 15, 3, UPPER_RIGHT, BOTTOM_LEFT)
t = Data('t', 15, 3, UPPER_LEFT, BOTTOM_RIGHT)
u = Data('u', 15, 3, UPPER_LEFT, BOTTOM_RIGHT)
v = Data('v', 15, 3, UPPER_LEFT, UPPER_RIGHT)
w = Data('w', 20, 5, UPPER_LEFT, UPPER_RIGHT)
x = Data('x', 13, 3, UPPER_LEFT, BOTTOM_RIGHT)
y = Data('y', 15, 3, UPPER_LEFT, BOTTOM_LINE)
z = Data('z', 15, 3, UPPER_LEFT, BOTTOM_RIGHT)


def rm_trainingdata(old_fn, new_fn):
    with open(old_fn, "r") as rf, open(new_fn, "w") as wf:
        data = ndjson.load(rf)
        for i, d in enumerate(data):
            if data_dic[d['kana']].m_max_in < len(d['events']):
                print(i, d['kana'], "Greater than maximum")
                continue
            if data_dic[d['kana']].m_min_in > len(d['events']):
                print(i, d['kana'], "Less than minimum")
                continue
            if not d['events'][0][0] in data_dic[d['kana']].m_start:
                print(i, d['kana'], "Starting point is different")
                continue
            if not d['events'][-1][0] in data_dic[d['kana']].m_finish:
                print(i, d['kana'], "End point is different")
                continue
            ndjson.dump([d], wf)
            wf.write("\n")


if __name__ == '__main__':
    args = sys.argv
    rm_trainingdata(args[1], args[2])
