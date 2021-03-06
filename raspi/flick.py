class Key:
    def __init__(self, pin, name, chr):
        self.pin = pin
        self.name = name
        self.chr = chr

    def __repr__(self):
        return self.name


class Gesture:
    def __init__(self, key_lst, process, output, mode, unique_key=False):
        self.key_lst = key_lst
        self.process = process
        self.output = output
        self.interval = 50
        self.mode = mode
        self.unique_key = unique_key

    def judge_gesture(self, input_lst):
        if self.unique_key:
            if self.key_lst == input_lst:
                out = self.process(self.output)
                return 1, out
            else:
                return 0, None
        else:
            if self.key_lst == input_lst[0:2]:
                out = self.process(self.output)
                return 1, out
            else:
                return 0, None
