#ifndef INCLUDE_GUARD_FLICK_HPP
#define INCLUDE_GUARD_FLICK_HPP

#include "Arduino.h"
#include "bluetooth.hpp"

class Key
{
public:
    Key(int pin, String name);
    bool operator==(const Key& r) const;

private:
    int m_pin;
    String m_name;
};


class Gesture
{
public:
    Gesture(Key* key_lst, String output, int mode_, bool unique_key = false);
    int judge_gesture(Key* input_lst);

private:
    Key* m_key_lst;
    String m_output;
    int m_mode;
    bool m_unique_key;
};


class Keyboard
{
public:
    Keyboard(int key_num);

private:
    int m_key_num;
    int m_mode;
    int m_ulst;
    Key m_key_lst[];
    Gesture m_ges_lst[];
};


#endif  // INCLUDE_GUARD_FLICK_HPP
