#include "flick.hpp"

Key::Key(int pin, String name, char chr)
{
    m_pin = pin;
    m_name = name;
    m_chr = chr;
}

Gesture::Gesture(key_lst, process, output, int mode, bool unique_key = False)
{
    m_key_lst[] = key_lst[];
    m_process = process;
    m_output = output;
    m_mode = mode;
    m_unique_key = unique_key;
}
int judge_gesture(input_lst)
{
    if (m_unique_key)
        if (m_key_lst == input_lst) {
            out = m_process(self.output);
            return 1, out;
        } else {
            return 0, None;
        }
    else {
        if (m_key_lst == input_lst [0:2]) {
            out = m_process(self.output);
            return 1, out;
        } else {
            return 0, None;
        }
    }
}
