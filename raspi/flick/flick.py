class Key:
    def __init__(self, pin, chr):
        self.pin = pin
        self.chr = chr

    def __repr__(self):
        return self.chr


class Gesture:
    def __init__(self, key_lst, process, output, mode):
        self.key_lst = key_lst
        self.process = process
        self.output = output
        self.interval = 50
        self.mode = mode

    def judge_gesture(self, input_lst):
        if self.key_lst == input_lst:
            self.process(self.output)
            return 1
        else:
            return 0
