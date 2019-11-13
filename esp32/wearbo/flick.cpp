#include "flick.hpp"

Key::Key(int pin, String name, String hwc, Wearbo& wearbo, bool unique_key)
{
    m_pin = pin;
    m_name = name;
    m_hwc = hwc;
    m_unique_key = unique_key;
    wearbo.m_key_lst[pin];
}

bool Key::operator!=(const Key& r) const
{
    return m_pin != r.m_pin && m_name != r.m_name;
}

Gesture::Gesture(Key* key_lst, int length, String output, int mode_)
{
    m_key_lst = key_lst;
    m_length = length;
    m_output = output;
    m_mode = mode_;
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
    m_cap = Adafruit_MPR121();

    if (!m_cap.begin(0x5A)) {
        Serial.println("MPR121 not found, check wiring?");
        while (1)
            ;
    }
    Serial.println("MPR121 found!");

    m_lasttouched = 0;
    m_currtouched = 0;
}

void Wearbo::main()
{
    int length = 0;
    TouchData* input_lst;
    String input_data = "";
    String input_time = "";
    record(input_data, input_time);
    if (m_mode == 0 || m_mode == 1) {
        String output = "";
        for (auto g : m_ges_lst) {
            output = g.judge_gesture(length, input_lst);
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
        } else {
            send_ble(output);
        }
    }
}

void Wearbo::record(String& input_data, String& input_time)
{
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    int rec = 0;
    unsigned long start_time = 0;
    unsigned long last_now = 0;
    unsigned long rec_time = 0;
    unsigned long ep_time_from_last = 0;
    unsigned long now_ = 0;
    int wait_seconds = 300;
    while (true) {
        uint16_t currtouched = m_cap.touched();

        if (rec == 0) {
            rec = 1;
            start_time = now();
            last_now = start_time;
        }

        for (uint8_t i = 0; i < 12; i++) {
            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
                last_now = now();
                rec_time = (last_now - start_time) * 1000;
                if (input_data.indexOf(m_key_lst[i].m_hwc) == -1) {
                    input_data.concat(m_key_lst[i].m_hwc);
                    input_time.concat((String)rec_time);
                    input_time.concat(" ");
                }
            }
        }

        now_ = now();
        ep_time_from_last = (now_ - last_now).total_seconds() * 1000;
        if (abs(ep_time_from_last) > wait_seconds && start_time != last_now) {
            break;
        }
        lasttouched = currenttouched;
    }
}

void Wearbo::change_mode(int next_mode)
{
    m_mode = next_mode;
}

void Wearbo::change_ulst()
{
    if (m_ulst == 1) {
        m_ulst = 0;
    } else {
        m_ulst = 1;
    }
}
