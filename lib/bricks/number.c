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

FxB_Number *FxB_Exponent_from_string(char *str) {
  FxB_Number *decimal = FxB_Number_create();
  verify(decimal);
  int type;

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

  if (is_big) {
    long double number_value;
    sscanf(str, format, &number_value);
    fxb_number_create_value(decimal, long double);
    type = FXB_DECIMAL_LDOUBLE;
  } else {
    double number_value;
    sscanf(str, format, &number_value);
    fxb_number_create_value(decimal, double);
    type = FXB_DECIMAL_DOUBLE;
  }

  fxb_number_exponent(decimal) = true;
  fxb_number_type(decimal) = type;

  return decimal;
error:
  if (decimal) { fx_pfree(decimal); }
  return NULL;
}

FxB_String *fxb_number_inspect(FxB_Number *number) {
  char str[200];

  char *format;
  if (fxb_number_is_decimal(number)) {
    if (fxb_number_exponent(number)) {
      if (fxb_number_type(number) == FXB_DECIMAL_DOUBLE) {
        sprintf(str, "%.1le", fxb_number_value_double(number));
      } else {
        sprintf(str, "%.1Le", fxb_number_value_ldouble(number));
      }
    } else {
      if (fxb_number_type(number) == FXB_DECIMAL_DOUBLE) {
        sprintf(str, "%.3le", fxb_number_value_double(number));
      } else {
        sprintf(str, "%.3Le", fxb_number_value_ldouble(number));
      }
    }
  } else {
    if (fxb_number_type(number) == FXB_INT_SHORT) {
      sprintf(str, "%d", fxb_number_value_short(number));
    } else if (fxb_number_type(number) == FXB_INT_STANDARD) {
      sprintf(str, "%d", fxb_number_value_standard(number));
    } else if (fxb_number_type(number) == FXB_INT_LONG) {
      sprintf(str, "%ld", fxb_number_value_long(number));
    } else {
      sprintf(str, "%lld", fxb_number_value_llong(number));
    }
  }

  FxB_String *string = FxB_String_create(str);
  verify(string);
error:
  return NULL;
}
