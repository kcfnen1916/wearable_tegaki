#include "flick.hpp"
// #include "config.hpp"

// Gesture ges_lst[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

Key::Key(int pin, String name, String hwc, Wearbo& wearbo, bool unique_key)
{
    m_pin = pin;
    m_name = name;
    m_hwc = hwc;
    m_unique_key = unique_key;
    wearbo.m_key_lst[pin] = hwc;
}

// Key Key::operator=(const Key& k)
// {
//     m_pin = k.m_pin;
//     m_name = k.m_name;
//     m_hwc = k.m_hwc;
//     m_unique_key = k.m_unique_key;
//     return *this;
// }

bool Key::operator!=(const Key& r) const
{
    return m_pin != r.m_pin && m_name != r.m_name;
}

Gesture::Gesture(String key_lst, int length, String output, int mode_)
{
    // m_key_lst = "";
    // for (int i = 0; i < length; i++) {
    //     m_key_lst.concat(key_lst[i].m_hwc);
    // }
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
    // for (int i = 0; i < count; i++) {
    if (input_data.indexOf(m_key_lst) == 0) {
        eq_flg = true;
        // break;
    }
    // }

    if (eq_flg) {
        return m_output;
    } else {
        return "NOT";
    }
}


Wearbo::Wearbo(int key_num)
{
    m_key_num = key_num;
    m_mode = 2;
    m_ulst = 0;
    // m_key_lst[12] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};
    // m_ges_lst[];
    m_lasttouched = 0;
    m_currtouched = 0;
    m_input_data = "";
    m_input_time = "";
    m_unique = false;
    m_send_data = "";
}

void Wearbo::main()
{
    // int length = 0;
    // while (1) {
    // m_input_data = "";
    // m_input_time = "";
    // m_unique = false;
    // record();
    // if (m_mode == 1 || m_mode == 2) {
    //     String output = "";
    //     for (auto g : ges_lst) {
    //         output = g.judge_gesture(m_input_data);
    //         if (output != "NOT") {
    //             break;
    //         }
    //     }
    //
    //     if (output == "CHANGE_ULST") {
    //         change_ulst();
    //     } else if (output == "CHANGE_MODE1") {
    //         change_mode(1);
    //     } else if (output == "CHANGE_MODE2") {
    //         change_mode(2);
    //     } else {
    //         Serial.println(output);
    //         send_ble(output);
    //     }
    // } else if (m_mode = 3) {
    //     if (m_unique) {
    //         String output = "";
    //         for (auto g : ges_lst) {
    //             output = g.judge_gesture(m_input_data);
    //             if (output != "NOT") {
    //                 break;
    //             }
    //         }
    //
    //         if (output == "CHANGE_ULST") {
    //             change_ulst();
    //         } else if (output == "CHANGE_MODE1") {
    //             change_mode(1);
    //         } else if (output == "CHANGE_MODE2") {
    //             change_mode(2);
    //         } else {
    //             send_ble(output);
    //         }
    //     } else {
    //         send_hwd();
    //     }
    // }
    // }
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
                // if (m_input_data.length() == 0) {
                //     dacWrite(26, 100);
                // }
                last_now = millis();
                rec_time = (last_now - start_time) * 1000;
                // if (m_input_data.indexOf(m_key_lst[i]) == -1) {
                if ((String)m_input_data.charAt(m_input_data.length() - 1) != m_key_lst[i]) {
                    m_input_data.concat(m_key_lst[i]);
                    // m_input_time.concat((String)rec_time);
                    // m_input_time.concat(" ");
                    // Serial.println("touched!");
                    if (m_input_data.length() == 1 && (m_key_lst[i] == "d" || m_key_lst[i] == "s" || m_key_lst[i] == "c")) {
                        m_unique = true;
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
    //Serial.println(m_input_data);
}

void Wearbo::send_hwd()
{
    // m_send_data = "";
    // m_send_data.concat(m_input_data);
    // m_send_data.concat(":");
    // m_send_data.concat(m_input_time);
    // client.print(m_send_data);
}

void Wearbo::receive_hwd()
{
    // while (1) {
    //     if (client.available() > 0) {
    //         send_ble((String)client.read());
    //     }
    // }
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
