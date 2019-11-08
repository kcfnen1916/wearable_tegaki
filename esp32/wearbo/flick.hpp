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
    Key(int pin, String name, char hwc, Wearbo& wearbo, bool unique_key = false);
    bool operator!=(const Key& r) const;

private:
    int m_pin;
    String m_name;
    char m_hwc;
    bool m_unique_key;
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
    Gesture(Key* key_lst, int length, String output, int mode_);
    String judge_gesture(int length, TouchData* input_lst);

private:
    Key* m_key_lst;
    int m_length;
    String m_output;
    int m_mode;
    // bool m_unique_key;  // true : 3*3以外のキーで始まる; false : 3*3以外のキーで始まらない;
    // int m_internal;     // 0 : 通常; 1 : モード切替; 2 : 大文字小文字切替;
};


class Wearbo
{
public:
    Wearbo(int key_num);
    void main();
    void record(int* length, TouchData* input_lst);
    // int search_gesture(TouchData* input_lst);
    void send_hwd(TouchData* input_lst);
    void receive_hwd();
    void change_mode(int next_mode);
    void change_ulst();
    Key m_key_lst[];

private:
    int m_key_num;
    int m_mode;  //0 : 英字フリック入力モード; 1 : 数字フリック入力モード;	2 : 手書き入力モード;
    int m_ulst;  //0 : 小文字; 1 : 大文字;
    Gesture m_ges_lst[];
    Adafruit_MPR121 m_cap;
    uint16_t m_lasttouched;
    uint16_t m_currtouched;
};


#endif  // INCLUDE_GUARD_FLICK_HPP
