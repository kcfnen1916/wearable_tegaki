#ifndef INCLUDE_GUARD_LEVENSHTEIN_DISTANCE_HPP
#define INCLUDE_GUARD_LEVENSHTEIN_DISTANCE_HPP
#include "Arduino.h"

int min(int a, int b);
int levenshtein_distance(String a, String b, int index);
#endif  // INCLUDE_GUARD_LEVENSHTEIN_DISTANCE_HPP