#include "flick.hpp"

Key::Key(int pin, String name)
{
    m_pin = pin;
    m_name = name;
}

bool Key::operator==(const Key& r) const
{
    return m_pin == r.m_pin && m_name == r.m_name;
}

Gesture::Gesture(Key* key_lst, String output, int mode_, bool unique_key)
{
    m_key_lst = key_lst;
    m_output = output;
    m_mode = mode_;
    m_unique_key = unique_key;
}

Keyboard::Keyboard(int key_num)
{
    m_key_num = key_num;
    m_mode = 0;
    m_ulst = 0;
    m_key_lst[12];
    m_ges_lst[];
}

int Gesture::judge_gesture(Key* input_lst)
{
    if (m_unique_key)
        if (&m_key_lst == &input_lst) {
            send_ble(m_output);
            return 1;
        } else {
            return 0;
        }
    else {
        if (m_key_lst[0] == input_lst[0] && m_key_lst[1] == input_lst[1]) {
            send_ble(m_output);
            return 1;
        } else {
            return 0;
        }
    }
}
