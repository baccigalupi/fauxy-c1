#ifndef __bricks
#define __bricks

#include <math.h>

// Used by both Array and String to get next capacity
static inline int Expandable_capacity(int capacity) {
  int exponent = 1;
  while ( capacity > 1 ) {
    exponent ++;
    capacity = capacity >> 1;
  }
  return pow(2, exponent+1);
}

#endif