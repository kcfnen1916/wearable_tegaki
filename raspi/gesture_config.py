from flick import *
# import flick
import struct

mode = 3
upper_flag = False

# Keyの宣言
# 雑実装のキー配置
# ijkl = Key(0, 'ijkl', 'u')
# delete = Key(1, 'delete', '-')
# space = Key(2, 'space', '-')
# wxyzh = Key(3, 'wxyzh', 'j')
# pcqe = Key(4, 'pcqe', 'm')
# brqdq = Key(5, 'brqdq', 'n')
# rstuv = Key(6, 'rstuv', 'h')
# assc = Key(7, 'assc', 'b')
# mnopq = Key(8, 'mnopq', 'g')
# cul = Key(9, 'cul', '-')
# abcd = Key(10, 'abcd', 't')
# efgh = Key(11, 'efgh', 'y')

# 染谷研プロトタイプのキー配置
# delete = Key(0, 'delete', '-')
# space = Key(1, 'space', '-')
# ijkl = Key(2, 'ijkl', 'u')
# wxyzh = Key(3, 'wxyzh', 'j')
# pcqe = Key(4, 'pcqe', 'm')
# efgh = Key(5, 'efgh', 'y')
# rstuv = Key(6, 'rstuv', 'h')
# brqdq = Key(7, 'brqdq', 'n')
# abcd = Key(8, 'abcd', 't')
# mnopq = Key(9, 'mnopq', 'g')
# assc = Key(10, 'assc', 'b')
# cul = Key(11, 'cul', '-')

# 完成品
delete = Key(11, 'delete', '-')
space = Key(10, 'space', '-')
ijkl = Key(9, 'ijkl', 'u')
wxyzh = Key(8, 'wxyzh', 'j')
pcqe = Key(7, 'pcqe', 'm')
efgh = Key(6, 'efgh', 'y')
rstuv = Key(5, 'rstuv', 'h')
brqdq = Key(4, 'brqdq', 'n')
abcd = Key(3, 'abcd', 't')
mnopq = Key(2, 'mnopq', 'g')
assc = Key(1, 'assc', 'b')
cul = Key(0, 'cul', '-')


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
# spc = Gesture([space], out_chr, ' ', 0)
# dlt = Gesture([delete], out_cmd, 8, 0)
# enter = Gesture([delete, space, pcqe], out_cmd, 10, 0, True)
# mode_r = Gesture([space, wxyzh, rstuv, mnopq, cul], change_mode, 'r', 0, True)
# mode_l = Gesture([cul, mnopq, rstuv, wxyzh, space], change_mode, 'l', 0, True)
# right = Gesture([cul, abcd, efgh, ijkl, delete], out_cmd, 7, 0, True)
# left = Gesture([delete, ijkl, efgh, abcd, cul], out_cmd, 11, 0, True)

# アルファベットフリック入力モード 1
# a = Gesture([abcd], out_alph, 'a', 1)
# b = Gesture([abcd, cul], out_alph, 'b', 1)
# c = Gesture([abcd, efgh], out_alph, 'c', 1)
# d = Gesture([abcd, mnopq], out_alph, 'd', 1)
# e = Gesture([efgh], out_alph, 'e', 1)
# f = Gesture([efgh, abcd], out_alph, 'f', 1)
# g = Gesture([efgh, ijkl], out_alph, 'g', 1)
# h = Gesture([efgh, rstuv], out_alph, 'h', 1)
# i = Gesture([ijkl], out_alph, 'i', 1)
# j = Gesture([ijkl, efgh], out_alph, 'j', 1)
# k = Gesture([ijkl, delete], out_alph, 'k', 1)
# l = Gesture([ijkl, wxyzh], out_alph, 'l', 1)
# m = Gesture([mnopq], out_alph, 'm', 1)
# n = Gesture([mnopq, cul], out_alph, 'n', 1)
# o = Gesture([mnopq, abcd], out_alph, 'o', 1)
# p = Gesture([mnopq, rstuv], out_alph, 'p', 1)
# q = Gesture([mnopq, assc], out_alph, 'q', 1)
# r = Gesture([rstuv], out_alph, 'r', 1)
# s = Gesture([rstuv, mnopq], out_alph, 's', 1)
# t = Gesture([rstuv, efgh], out_alph, 't', 1)
# u = Gesture([rstuv, wxyzh], out_alph, 'u', 1)
# v = Gesture([rstuv, brqdq], out_alph, 'v', 1)
# w = Gesture([wxyzh], out_alph, 'w', 1)
# x = Gesture([wxyzh, rstuv], out_alph, 'x', 1)
# y = Gesture([wxyzh, ijkl], out_alph, 'y', 1)
# z = Gesture([wxyzh, space], out_alph, 'z', 1)
# hyphen = Gesture([wxyzh, pcqe], out_chr, '-', 1)
# at = Gesture([assc], out_chr, '@', 1)
# slash = Gesture([assc, cul], out_chr, '/', 1)
# sharp = Gesture([assc, mnopq], out_chr, '#', 1)
# colon = Gesture([assc, brqdq], out_chr, ':', 1)
# brcl = Gesture([brqdq], out_chr, '(', 1)
# brcr = Gesture([brqdq, assc], out_chr, ')', 1)
# quot = Gesture([brqdq, rstuv], out_chr, "'", 1)
# dubquot = Gesture([brqdq, pcqe], out_chr, '"', 1)
# period = Gesture([pcqe], out_chr, '.', 1)
# comma = Gesture([pcqe, brqdq], out_chr, ',', 1)
# question = Gesture([pcqe, wxyzh], out_chr, '?', 1)
# exclam = Gesture([pcqe, space], out_chr, '!', 1)
# chuplow = Gesture([cul], set_upper_flag, None, 1)

# 数字入力モード 2
# zero = Gesture([cul], out_num, '0', 2)
# one = Gesture([abcd], out_num, '1', 2)
# two = Gesture([efgh], out_num, '2', 2)
# three = Gesture([ijkl], out_num, '3', 2)
# four = Gesture([mnopq], out_num, '4', 2)
# five = Gesture([rstuv], out_num, '5', 2)
# six = Gesture([wxyzh], out_num, '6', 2)
# seven = Gesture([assc], out_num, '7', 2)
# eight = Gesture([brqdq], out_num, '8', 2)
# nine = Gesture([pcqe], out_num, '9', 2)

right = Gesture([space], out_cmd, 7, 0, True)
left = Gesture([cul], out_cmd, 11, 0, True)

# Key list
# 雑実装のキー配置
# key_lst = [ijkl, delete, space, wxyzh, pcqe, brqdq, rstuv, assc, mnopq, cul, abcd, efgh]
# 染谷研プロトタイプのキー配置
# key_lst = [delete, space, ijkl, wxyzh, pcqe, efgh, rstuv, brqdq, abcd, mnopq, assc, cul]
key_lst = [cul, assc, mnopq, abcd, brqdq, rstuv, efgh, pcqe, wxyzh, ijkl, space, delete]

# Gesture list
# ges_lst = [[spc, dlt, enter, mode_l, mode_r, right, left, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, hyphen, at, slash, sharp, colon, brcl, brcr, quot, dubquot, period, comma, question, exclam, chuplow], [spc, dlt, enter, mode_l, mode_r, right, left, zero, one, two, three, four, five, six, seven, eight, nine], [spc, dlt, enter, mode_l, mode_r, right, left]]
ges_lst = [right, left]
