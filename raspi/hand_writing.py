hw_lst = []

class HandWriting:
    def __init__(self, chr,length, begin, end, via = None):
        self.chr = chr
        self.length = length
        self.begin = begin
        self.end = end
        if via == None:
            self.via = begin
        else:
            self.via = via
        hw_lst.append(self)

    def __repr__(self):
        return self.chr

a_hw = HandWriting('a', 11, 'u', 'm', 'j')
x_hw = HandWriting('x', 6, 't', 'b', 'm')
b_hw = HandWriting('b', 7, 't', 'b', 'n')
c_hw = HandWriting('c', 7, 'u', 'm', 'g')
d_hw = HandWriting('d', 8, 'j', 'm')
d_hw2 = HandWriting('d', 8, 'h', 'n')
e_hw = HandWriting('e', 10, 'g', 'm', 'b')
f_hw = HandWriting('f', 7, 'u', 'j')
g_hw = HandWriting('g', 8, 'u', 'n')
g_hw2 = HandWriting('g', 8, 'y', 'b')
h_hw = HandWriting('h', 6, 't', 'n') # TODO
h_hw2 = HandWriting('h', 6, 'y', 'm') # TODO
i_hw = HandWriting('i', 3, 'h', 'y')
i_hw2 = HandWriting('i', 3, 'g', 't')
i_hw3 = HandWriting('i', 3, 'j', 'u')
j_hw = HandWriting('j', 4, 'h', 'y', 'b')
j_hw2 = HandWriting('j', 4, 'j', 'u', 'n')
k_hw = HandWriting('k', 6, 't', 'n') # TODO
p_hw2 = HandWriting('p', 7, 'y', 'n', 'u')
b_hw2 = HandWriting('b', 7, 'y', 'n', 'm')
q_hw2 = HandWriting('q', 7, 'y', 'n', 't')
l_hw = HandWriting('l', 3, 'y', 'n')
l_hw2 = HandWriting('l', 3, 't', 'b')
l_hw3 = HandWriting('l', 3, 'u', 'm')
m_hw = HandWriting('m', 13, 't', 'm')
z_hw = HandWriting('z', 7, 't', 'm', 'h')
n_hw = HandWriting('n', 9, 't', 'm', 'y')
o_hw = HandWriting('o', 9, 'y', 'y')
p_hw = HandWriting('p', 7, 't', 'b', 'y')
q_hw = HandWriting('q', 7, 'u', 'm', 'j')
r_hw = HandWriting('r', 7, 't', 'u', 'y')
s_hw = HandWriting('s', 9, 'u', 'b')
t_hw = HandWriting('t', 7, 'g', 'm')
u_hw = HandWriting('u', 9, 't', 'm', 'n')
v_hw = HandWriting('v', 7, 't', 'u', 'n')
w_hw = HandWriting('w', 10, 't', 'u')
y_hw = HandWriting('y', 5, 't', 'b')


hw_dic = {}

for hw in hw_lst:
    k = hw.begin + hw.end
    if not k in hw_dic:
        hw_dic[k] = []
    hw_dic[k].append(hw)



def argmin(arr):
    return [i for i, v in enumerate(arr) if v == min(arr)]


def judge_hand_writing(input_lst):
    input_data = [inp[0] for inp in input_lst]
    k = input_data[0] + input_data[-1]
    if k in hw_dic:
        if len(hw_dic[k]) == 1:
            return hw_dic[k][0].chr
        else:
            argmin_lst = argmin([abs(hw.length - len(input_data)) for hw in hw_dic[k]])
            if len(argmin_lst) == 1:
                return hw_dic[k][argmin_lst[0]].chr
            else:
                for am in argmin_lst:
                    if hw_dic[k][am].via in input_data:
                        return hw_dic[k][am].chr
    return '='

if __name__=='__main__':
    print(hw_dic)
    print(judge_hand_writing([('h',0),('n',100),('b',200),('y',300)]))
