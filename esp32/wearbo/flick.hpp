#ifndef INCLUDE_GUARD_FLICK_HPP
#define INCLUDE_GUARD_FLICK_HPP

#include "Adafruit_MPR121.h"
#include "Arduino.h"
#include "bluetooth.hpp"
#include <Wire.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

class Wearbo;

class Key
{
public:
    Key(int pin, String name, String hwc, Wearbo& wearbo, bool unique_key = false);
    bool operator!=(const Key& r) const;
    Key operator=(const Key& k);
    String m_hwc;
    bool m_unique_key;

private:
    int m_pin;
    String m_name;
};

class TouchData
{
public:
    TouchData(Key m_key, unsigned long m_time);
    String data2str();

    Key m_key;
    unsigned long m_time;
};


class Gesture
{
public:
    Gesture(String key_lst, int length, String output, int mode_);
    String judge_gesture(String input_data);
    Gesture operator=(const Gesture& r);
    String m_output;
    int m_mode;

private:
    String m_key_lst;
    int m_length;
    // bool m_unique_key;  // true : 3*3以外のキーで始まる; false : 3*3以外のキーで始まらない;
    // int m_internal;     // 0 : 通常; 1 : モード切替; 2 : 大文字小文字切替;
};

extern Gesture ges_lst[];

class Wearbo
{
public:
    Wearbo(int key_num);
    void main();
    void record();
    void send_hwd();
    void receive_hwd();
    void change_mode(int next_mode);
    void change_ulst();
    String m_key_lst[12] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};

    Adafruit_MPR121 m_cap;
    // Gesture m_ges_lst[];

    int m_key_num;
    int m_mode;  //0 : 共通;　1 : 英字フリック入力モード; 2 : 数字フリック入力モード;	3 : 手書き入力モード;
    int m_ulst;  //0 : 小文字; 1 : 大文字;
    uint16_t m_lasttouched;
    uint16_t m_currtouched;
    String m_input_data;
    String m_input_time;
    boolean m_unique;
    String m_send_data;
};


#endif  // INCLUDE_GUARD_FLICK_HPP
