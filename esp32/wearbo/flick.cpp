#include "flick.hpp"

Key::Key(int pin, String name, String hwc, Wearbo& wearbo, bool unique_key)
{
    m_pin = pin;
    m_name = name;
    m_hwc = hwc;
    m_unique_key = unique_key;
    wearbo.m_key_lst[pin] = hwc;
}

bool Key::operator!=(const Key& r) const
{
    return m_pin != r.m_pin && m_name != r.m_name;
}

Gesture::Gesture(String key_lst, int length, String output, int mode_)
{
    m_key_lst = key_lst;
    m_length = length;
    m_output = output;
    m_mode = mode_;
}

Gesture Gesture::operator=(const Gesture& g)
{
    m_key_lst = g.m_key_lst;
    m_length = g.m_length;
    m_output = g.m_output;
    m_mode = g.m_mode;
    return *this;
}

String Gesture::judge_gesture(String input_data)
{
    bool eq_flg = false;
    int count = min((int)input_data.length(), (int)m_length);
    if (input_data.indexOf(m_key_lst) == 0) {
        eq_flg = true;
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
    m_mode = 3;
    m_ulst = 0;
    m_lasttouched = 0;
    m_currtouched = 0;
    m_input_data = "";
    m_input_time = "";
    m_unique = false;
    m_send_data = "";
}

void Wearbo::record()
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
    //Serial.println("recoding...");
    while (true) {
        currtouched = m_cap.touched();
        if (rec == 0) {
            rec = 1;
            start_time = millis();
            last_now = start_time;
        }
        for (uint8_t i = 0; i < 12; i++) {
            if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
                last_now = millis();
                rec_time = (last_now - start_time) * 1000;
                if ((String)m_input_data.charAt(m_input_data.length() - 1) != m_key_lst[i]) {
                    if ((m_key_lst[i] != "d") && (m_key_lst[i] != "c") && (m_key_lst[i] != "s")){
                        m_input_data.concat(m_key_lst[i]);
                        if (m_input_data.length() == 1){
                            if (m_key_lst[i] == "d" || m_key_lst[i] == "s" || m_key_lst[i] == "c"){
                                m_unique = true;
                            }
                            else{
                                break;
                            }
                        }
                    }
                }
            }
        }
        now_ = millis();
        ep_time_from_last = now_ - last_now;
        if (abs(ep_time_from_last) > wait_seconds && start_time != last_now) {
            break;
        }
        lasttouched = currtouched;
    }
    Serial.println(m_input_data);
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
