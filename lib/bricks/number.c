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

FxB_Number *FxB_Integer_from_string(char *str) {
  FxB_Number *integer = FxB_Number_create();
  verify(integer);

  errno = 0;
  char *last_char;
  long long number_value = strtoll(str, &last_char, 10);
  errno = 0; // reset

  int type;
  void *value;
  if (ERANGE == errno) {
    print_error("Integer out of range");
    goto error;
  } else {
    if ( number_value <= SHRT_MAX ) {
      fxb_number_create_value(integer, short);
      type = FXB_INT_SHORT;
    } else if ( number_value <= INT_MAX ) {
      fxb_number_create_value(integer, int);
      type = FXB_INT_STANDARD;
    } else if ( number_value <= LONG_MAX ) {
      fxb_number_create_value(integer, long);
      type = FXB_INT_LONG;
    } else {
      fxb_number_create_value(integer, long long);
      type = FXB_INT_LLONG;
    }
  }

  fxb_number_type(integer) = type;

  return integer;
error:
  if (integer) { fx_pfree(integer); }
  return NULL;
}

FxB_Number *FxB_Decimal_from_string(char *str) {
  FxB_Number *decimal = FxB_Number_create();
  verify(decimal);

  int type;
  if (strlen(str) - 1 <= DBL_DIG) {
    double number_value;
    sscanf(str, "%lf", &number_value);
    fxb_number_create_value(decimal, double);
    type = FXB_DECIMAL_DOUBLE;
  } else {
    long double number_value;
    sscanf(str, "%Lf", &number_value);
    fxb_number_create_value(decimal, long double);
    type = FXB_DECIMAL_LDOUBLE;
  }

  fxb_number_type(decimal) = type;

  return decimal;
error:
  if (decimal) { fx_pfree(decimal); }
  return NULL;
}
