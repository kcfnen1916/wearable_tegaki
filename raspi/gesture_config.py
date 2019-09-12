from flick import *
#import flick
import struct

mode = 1
upper_flag = False

# Keyの宣言
# 雑実装のキー配置
hij = Key(0, 'hij', 'u')
delete = Key(1, 'delete', '-')
space = Key(2, 'space', '-')
tuvw = Key(3, 'tuvw', 'j')
bracket = Key(4, 'bracket', 'm')
pcqe = Key(5, 'pcqe', 'n')
opqrs = Key(6, 'opqrs', 'h')
xyz = Key(7, 'xyz', 'b')
klmn = Key(8, 'klmn', 'g')
cul = Key(9, 'cul', '-')
abc = Key(10, 'abc', 't')
defg = Key(11, 'defg', 'y')

# 染谷研プロトタイプのキー配置
# delete = Key(0, 'delete', '-')
# space = Key(1, 'space', '-')
# hij = Key(2, 'hij', 'u')
# tuvw = Key(3, 'tuvw', 'j')
# bracket = Key(4, 'bracket', 'm')
# defg = Key(5, 'defg', 'y')
# opqrs = Key(6, 'opqrs', 'h')
# pcqe = Key(7, 'pcqe', 'n')
# abc = Key(8, 'abc', 't')
# klmn = Key(9, 'klmn', 'g')
# xyz = Key(10, 'xyz', 'b')
# cul = Key(11, 'cul', '-')


# Gestureによる処理の定義
def out_cmd(code):
    print("command : {}".format(code))
    return struct.pack('b', code)


def change_mode(d):
    global mode
    # print(d)
    if d == 'r':
        mode = min(mode + 1, 3)
        print("change mode", mode)
    elif d == 'l':
        mode = max(mode - 1, 1)
        print("change mode", mode)
    return None


def out_alph(c):
    if upper_flag:
        print(str.upper(c))
        return str.upper(c)
    else:
        print(c)
        return c


def out_chr(c):
    print(c)
    return c


def out_num(n):
    print(n)
    return n


def set_upper_flag(arg):
    global upper_flag
    upper_flag = not upper_flag
    return None


# Gestureの宣言
# モード共通 0
spc = Gesture([space], out_chr, ' ', 0)
dlt = Gesture([delete], out_cmd, 8, 0)
enter = Gesture([delete, space, bracket], out_cmd, 10, 0, True)
mode_r = Gesture([space, tuvw, opqrs, klmn, cul], change_mode, 'r', 0, True)
mode_l = Gesture([cul, klmn, opqrs, tuvw, space], change_mode, 'l', 0, True)
right = Gesture([cul, abc, defg, hij, dlt], out_cmd, 7, 0, True)
left = Gesture([dlt, hij, defg, abc, cul], out_cmd, 11, 0, True)

# アルファベットフリック入力モード 1
a = Gesture([abc], out_alph, 'a', 1)
b = Gesture([abc, defg], out_alph, 'b', 1)
c = Gesture([abc, klmn], out_alph, 'c', 1)
d = Gesture([defg], out_alph, 'd', 1)
e = Gesture([defg, hij], out_alph, 'e', 1)
f = Gesture([defg, opqrs], out_alph, 'f', 1)
g = Gesture([defg, abc], out_alph, 'g', 1)
h = Gesture([hij], out_alph, 'h', 1)
i = Gesture([hij, tuvw], out_alph, 'i', 1)
j = Gesture([hij, defg], out_alph, 'j', 1)
k = Gesture([klmn], out_alph, 'k', 1)
l = Gesture([klmn, opqrs], out_alph, 'l', 1)
m = Gesture([klmn, xyz], out_alph, 'm', 1)
n = Gesture([klmn, abc], out_alph, 'n', 1)
o = Gesture([opqrs], out_alph, 'o', 1)
p = Gesture([opqrs, tuvw], out_alph, 'p', 1)
q = Gesture([opqrs, pcqe], out_alph, 'q', 1)
r = Gesture([opqrs, klmn], out_alph, 'r', 1)
s = Gesture([opqrs, defg], out_alph, 's', 1)
t = Gesture([tuvw], out_alph, 't', 1)
u = Gesture([tuvw, bracket], out_alph, 'u', 1)
v = Gesture([tuvw, opqrs], out_alph, 'v', 1)
w = Gesture([tuvw, hij], out_alph, 'w', 1)
x = Gesture([xyz], out_alph, 'x', 1)
y = Gesture([xyz, pcqe], out_alph, 'y', 1)
z = Gesture([xyz, klmn], out_alph, 'z', 1)
period = Gesture([pcqe], out_chr, '.', 1)
comma = Gesture([pcqe, xyz], out_chr, ',', 1)
question = Gesture([pcqe, opqrs], out_chr, '?', 1)
exclam = Gesture([pcqe, bracket], out_chr, '!', 1)
brcl = Gesture([bracket], out_chr, '(', 1)
brcr = Gesture([bracket, pcqe], out_chr, ')', 1)
chuplow = Gesture([cul], set_upper_flag, None, 1)

# 数字入力モード 2
zero = Gesture([cul], out_num, '0', 2)
one = Gesture([abc], out_num, '1', 2)
two = Gesture([defg], out_num, '2', 2)
three = Gesture([hij], out_num, '3', 2)
four = Gesture([klmn], out_num, '4', 2)
five = Gesture([opqrs], out_num, '5', 2)
six = Gesture([tuvw], out_num, '6', 2)
seven = Gesture([xyz], out_num, '7', 2)
eight = Gesture([pcqe], out_num, '8', 2)
nine = Gesture([bracket], out_num, '9', 2)

# Key list
# 雑実装のキー配置
key_lst = [hij, delete, space, tuvw, bracket, pcqe, opqrs, xyz, klmn, cul, abc, defg]
# 染谷研プロトタイプのキー配置
# key_lst = [delete, space, hij, tuvw, bracket, defg, opqrs, pcqe, abc, klmn, xyz, cul]

# Gesture list
ges_lst = [[spc, dlt, enter, mode_l, mode_r, right, left, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y,
            z, period, comma, question, exclam, brcl, brcr, chuplow], [spc, dlt, enter, mode_l, mode_r, right, left, zero, one, two, three, four, five, six, seven, eight, nine], [spc, dlt, enter, mode_l, mode_r, right, left]]
