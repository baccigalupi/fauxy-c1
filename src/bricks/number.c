#include "number.h"
#include <limits.h>
#include <float.h>
#include <string.h>
#include <errno.h>

FxB_Number *FxB_Number_create() {
  FxB_Number *integer = fx_alloc(FxB_Number);
  verify_memory(integer);

  return integer;
error:
  return NULL;
}

// Simplified on 3/2/16 to always use a long long, inefficient but easy
FxB_Number *FxB_Integer_from_string(char *str) {
  FxB_Number *integer = FxB_Number_create();
  verify(integer);

  errno = 0;
  char *last_char;
  long long number_value = strtoll(str, &last_char, 10);
  errno = 0; // reset

  if (ERANGE == errno) {
    print_error("Integer out of range");
    goto error;
  } else {
    long long *value = fx_alloc(long long);
    verify_memory(value);
    *value = number_value;
    fxb_number_value(integer) = value;
    fxb_number_type(integer) = FX_INT_LLONG;
  }

  return integer;
error:
  if (integer) { fx_pfree(integer); }
  return NULL;
}

FxB_Number *FxB_Decimal_from_string(char *str) {
  FxB_Number *decimal = FxB_Number_create();
  verify(decimal);

  long double number_value;
  sscanf(str, "%Lf", &number_value);
  fxb_number_create_value(decimal, long double);
  fxb_number_type(decimal) = FX_DECIMAL_LDOUBLE;

  return decimal;
error:
  if (decimal) { fx_pfree(decimal); }
  return NULL;
}

FxB_Number *FxB_Exponent_from_string(char *str) {
  FxB_Number *decimal = FxB_Number_create();
  verify(decimal);

  char *format;
  int length = strlen(str);
  Boolean is_big_e = false;
  Boolean is_big = strlen(str) > DBL_DIG;
  int i;
  for (i = 0; i < length; i++) {
    if (str[i] == 'E') {
      is_big_e = true;
      break;
    }
  }
  if (is_big) {
    if (is_big_e) {
      format = "%LE";
    } else {
      format = "%Le";
    }
  } else {
    if (is_big_e) {
      format = "%lE";
    } else {
      format = "%le";
    }
  }


  long double number_value;
  sscanf(str, format, &number_value);
  fxb_number_create_value(decimal, long double);
  fxb_number_exponent(decimal) = true;
  fxb_number_type(decimal) = FX_DECIMAL_LDOUBLE;

  return decimal;
error:
  if (decimal) { fx_pfree(decimal); }
  return NULL;
}

FxB_String *fxb_number_type_description(FxB_Number *number) {
  int type = fxb_number_type(number);
  FxB_String *string = NULL;
  if (type == FX_INT_LLONG) {
    string = FxB_String_create("INTEGER");
  } else {
    string = FxB_String_create("DECIMAL");
  }
  return string;
}
