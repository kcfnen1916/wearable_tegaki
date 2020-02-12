#include "one_dim_hw.hpp"

HWData::HWData(float data_lst, String output, OneDimHW& parent)
{
    m_data_lst = data_lst;
    m_output = output;
    // parent.m_hw_data_lst = this;
}

OneDimHW::OneDimHW(int sensor_num)
{
    m_sensor_num = sensor_num;
    // m_input_data[80][2] = {{}, {}};
    m_estim_data = 0;
    m_output = "";
    m_lasttouched = 0;
    m_currtouched = 0;
}

void OneDimHW::record()
{
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    bool rec_start = false;
    // unsigned long start_time = 0;
    unsigned long last_now = 0;
    // unsigned long rec_time = 0;
    unsigned long ep_time_from_last = 0;
    unsigned long now_ = 0;
    int wait_seconds = 300;
    for (int i = 0; i < 80; i++) {
        m_input_data[0][i] = -1.0;
        m_input_data[1][i] = -1.0;
    }

    boolean now_touch[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
    float now_status = -1.0;
    float last_status = -1.0;
    int i = 0;
    Serial.println("recoding...");

    while (true) {
        currtouched = m_cap.touched();
        now_ = millis();

        for (int j = 0; j < 12; j++) {
            if ((currtouched & _BV(j)) && !(lasttouched & _BV(j))) {
                now_touch[j] = true;
                if (!rec_start) {
                    rec_start = true;
                }
                // last_now = millis();
                // rec_time = (last_now - start_time) * 1000;
            }
            if (!(currtouched & _BV(j)) && (lasttouched & _BV(j))) {
                now_touch[j] = false;
                // Serial.print(i);
                // Serial.println(" released");
            }
            if (now_touch[j]) {
                if (now_status == -1.0) {
                    now_status = j;
                } else {
                    now_status = ((float)(now_status + j)) / 2.0;
                }
            }
        }

        if (now_status != last_status) {
            m_input_data[0][i] = now_status;
            if (i != 0) {
                m_input_data[1][i - 1] = (float)(now_ - last_now);
            }
            last_now = now_;
        }

        ep_time_from_last = now_ - last_now;
        if (abs(ep_time_from_last) > wait_seconds && rec_start && now_status == -1.0) {
            break;
        }
        lasttouched = currtouched;
        last_status = now_status;
        now_status = -1.0;
    }
    // Serial.println(m_input_data);
}

void OneDimHW::scale()
{
}

void OneDimHW::estimate()
{
}
