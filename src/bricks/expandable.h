#ifndef __FxB_Expandable_h
#define __FxB_Expandable_h

#include <math.h>

// Used by both FxB_Array and FxB_String to get next capacity
static inline int FxB_Expandable_capacity(int capacity) {
  int exponent = 1;
  while ( capacity > 1 ) {
    exponent ++;
    capacity = capacity >> 1;
  }
  return pow(2, exponent+1);
}

#endif
