#ifndef __bricks
#define __bricks

#include <math.h>

#define CONSOLE_RED      "\e[31m"
#define CONSOLE_GREEN    "\e[38;5;40m"
#define CONSOLE_ORANGE   "\e[40;38;5;214m"
#define CONSOLE_RESET    "\e[0m"

typedef enum {
  false,
  true
} Boolean;

// MEMORY -----------
// frees a pointer and sets it to null
#define pfree(P)        ((P) != NULL) ? (free(P), ((P) = NULL)) : (NULL)

// VARIANT ACCESSORS -------------
#define object_type(O)       ((O)->type)
#define object_value(O)      ((O)->value)

// EXPANDABLE OBJECT METHODS
static inline int Expandable_capacity(int capacity) {
  int exponent = 1;
  while ( capacity > 1 ) {
    exponent ++;
    capacity = capacity >> 1;
  }
  return pow(2, exponent+1);
}

#endif
