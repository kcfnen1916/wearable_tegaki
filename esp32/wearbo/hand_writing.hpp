#ifndef INCLUDE_GUARD_HAND_WRITING_HPP
#define INCLUDE_GUARD_HAND_WRITING_HPP

#include "Arduino.h"

class HandWriting
{
public:
    HandWriting(String output, String pattern);

    String m_output;
    String m_pattern;
};

#endif  // INCLUDE_GUARD_HAND_WRITING_HPP
