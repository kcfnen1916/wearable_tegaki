#ifndef INCLUDE_GUARD_FLICK_HPP
#define INCLUDE_GUARD_FLICK_HPP

#include "Arduino.h"

class Key
{
public:
    Key(int pin, String name, char chr);

private:
    int m_pin;
    String m_name;
    char m_chr;
};

class Gesture
{
public:
    Gesture(key_lst, process, output, mode, unique_key = False);
    int judge_gesture(self, input_lst);

private:
    Key m_key_lst[];
    void m_process;
    int m_output;
    int m_mode;
    bool m_unique_key;
}

#endif  // INCLUDE_GUARD_FLICK_HPP
