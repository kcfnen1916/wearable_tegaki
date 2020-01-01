#ifndef INCLUDE_GUARD_ODHW_HPP
#define INCLUDE_GUARD_ODHW_HPP

#include "Adafruit_MPR121.h"
#include "Arduino.h"


#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif


class OneDimHW;


class HWData
{
public:
    HWData(float data_lst, String output, OneDimHW& parent);

private:
    float m_data_lst;  // 理想的な入力
    String m_output;   // 出力文字
};

class OneDimHW
{
public:
    OneDimHW(int sensor_num);
    void record();
    void scale();
    void estimate();
    Adafruit_MPR121 m_cap;

private:
    int m_sensor_num;           // センサーの数
    float m_input_data[2][80];  // 入力二次元配列{{タッチ位置},{時間}}
    float m_estim_data;         // 推定用のベクトル
    // HWData m_hw_data_lst;  // 定義ずみベクトルデータのリスト
    String m_output;  // 出力文字

    // 静電容量センサー関連
    uint16_t m_lasttouched;
    uint16_t m_currtouched;
};

#endif  // INCLUDE_GUARD_ODHW_HPP
