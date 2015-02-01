#include "number.h"
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
  int length = strlen(str);
  FxB_Number *integer = FxB_Number_create();
  verify(integer);

  errno = 0;
  char *last_char;
  long long int_value = strtoll(str, &last_char, 10);
  errno = 0; // reset

  int type;
  void *value;
  if (ERANGE == errno) {
    print_error("Integer out of range");
    goto error;
  } else {
    if ( int_value <= SHRT_MAX ) {
      fxb_number_create_value(integer, short);
      type = FXB_INT_SHORT;
    } else if ( int_value <= INT_MAX ) {
      fxb_number_create_value(integer, int);
      type = FXB_INT_STANDARD;
    } else if ( int_value <= LONG_MAX ) {
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
