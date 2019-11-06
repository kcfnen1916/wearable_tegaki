#include "flick.hpp"

Key::Key(int pin, String name, char hwc, Wearbo& wearbo, bool unique_key)
{
    m_pin = pin;
    m_name = name;
    m_hwc = hwc;
    m_unique_key = unique_key;
    wearbo.m_key_lst[pin];
}

bool Key::operator==(const Key& r) const
{
    return m_pin == r.m_pin && m_name == r.m_name;
}

Gesture::Gesture(Key* key_lst, String output, int length, int mode_, bool unique_key)
{
    m_key_lst = key_lst;
    m_length = length;
    m_output = output;
    m_mode = mode_;
    m_unique_key = unique_key;
}

String Gesture::judge_gesture(int length, TouchData* input_lst)
{
    bool eq_flg = true;
    if (m_length > length) {
        return "NOT";
    }
    int count = min(length, m_length);
    for (int i = 0; i < count; i++) {
        if (m_key_lst[i] != input_lst[i].m_key) {
            eq_flg = false;
            break;
        }
    }

    if (eq_flg) {
        return m_output;
    } else {
        return "NOT";
    }
}


Wearbo::Wearbo(int key_num)
{
    m_key_num = key_num;
    m_mode = 0;
    m_ulst = 0;
    m_key_lst[12];
    // m_ges_lst[];
}

void Wearbo::main()
{

    TouchData* input_lst = record();
    if (m_mode == 0 || m_mode == 1) {
        String output = "";
        for (auto g : m_gesture_config) {
            output = g.judge_gesture(input_lst);
            if (output != "NOT") {
                break;
            }
        }

        if (output == "CHANGE_ULST") {
            change_ulst();
        } else if (output == "CHANGE_MODE0") {
            change_mode(0);
        } else if (output == "CHANGE_MODE1") {
            change_mode(1);
            // } else if (output == "CHANGE_MODE2") {
            //     change_mode(2);
        } else {
            send_ble(output);
        }
    }
}
