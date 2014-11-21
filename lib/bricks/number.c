#include <stdlib.h>
#include <string.h>

#include "error_handling.h"
#include "bricks.h"

#include "number.h"


Number *Number_create(const char *str) {
  Number *number = calloc(1, sizeof(Number));
  check_mem(number);

  unsigned int is_float = 0;
  unsigned int i;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == '.' || str[i] == 'E') { is_float = 1; }
  }

  number_type(number) = is_float ? FloatType : IntegerType;
  is_float ? (number->value.as_float = A_TO_F(str)) : (number->value.as_int = A_TO_I(str));

  return number;
error:
  return NULL;
}

void number_convert(Number *number, int type) {
  if (number_type(number) == type) { return; }

  if (type == IntegerType) {
    FLOAT original = number_value(number);
    number_type(number) = IntegerType;
    number->value.as_int = (INT)original;
  } else {
    INT original = number_value(number);
    number_type(number) = FloatType;
    number->value.as_float = (FLOAT)original;
  }
}

void number_destroy(Number *number) {
  pfree(number);
}
