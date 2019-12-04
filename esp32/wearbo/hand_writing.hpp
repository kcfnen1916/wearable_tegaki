#ifndef INCLUDE_GUARD_HAND_WRITING_HPP
#define INCLUDE_GUARD_HAND_WRITING_HPP

#include "Arduino.h"

class HandWriting
{
public:
    HandWriting(String output, int length, String begin, String end, String via = "-");

    String m_output;
    int m_length;
    String m_begin;
    String m_end;
    String m_via;
};

#endif  // INCLUDE_GUARD_HAND_WRITING_HPP
