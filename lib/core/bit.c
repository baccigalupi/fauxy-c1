#include <string.h>

#include "bit.h"

#include "../parser/parse.tab.h"

#include "../bricks/bricks.h"
#include "../bricks/helpers.h"
#include "../bricks/string.h"


FauxyBit *FauxyBit_create(int token_type, char *text) {
  FauxyBit *bit = fx_alloc(FauxyBit);
  verify_memory(bit);

  int size = strlen(text);
  int type = FauxyBit_bit_type(token_type, fauxy_bit_size_is_small(size));
  fauxy_bit_type(bit) = type;
  fauxy_bit_size(bit) = size;

  Boolean success;
  if (type == FX_BIT_FLOAT) {
    success = fauxy_bit_add_float_value(bit, text);
  } /* else if (type == FX_BIT_LONG_FLOAT) {
    success = fauxy_bit_add_long_float_value(bit, text);
  } */ else if (type == FX_BIT_SHORT) {
    success = fauxy_bit_add_short_value(bit, text);
  } else if (type == FX_BIT_LONG) {
    success = fauxy_bit_add_long_value(bit, text);
  } else {
    success = fauxy_bit_add_string_value(bit, text);
  }
  verify(success);

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

int FauxyBit_bit_type(int token_type, Boolean is_small) {
  int bit_type;
  if (token_type == TOKEN_FLOAT) {
    bit_type = FX_BIT_FLOAT;
  } else if (token_type == TOKEN_INTEGER) {
    bit_type = is_small ? FX_BIT_SHORT : FX_BIT_LONG;
  } else {
    bit_type = FX_BIT_STRING;
  }

  return bit_type;
}

inline Boolean fauxy_bit_add_short_value(FauxyBit *bit, char *text) {
  short *value = calloc(1, sizeof(short));
  verify_memory(value);
  *value = atoi(text);
  fauxy_bit_value(bit) = value;

  return true;
error:
  return false;
}

Boolean fauxy_bit_add_long_value(FauxyBit *bit, char *text) {
  long long *value = calloc(1, sizeof(long long));
  verify_memory(value);
  char *endpoint;
  *value = strtoll(text, &endpoint, 10);
  fauxy_bit_value(bit) = value;


  return true;
error:
  return false;
}

Boolean fauxy_bit_add_float_value(FauxyBit *bit, char *text) {
  double *value = calloc(1, sizeof(float));
  verify_memory(value);
  *value = atof(text);
  fauxy_bit_value(bit) = value;

  return true;
error:
  return false;
}

// Boolean fauxy_bit_add_long_float_value(FauxyBit *bit, char *text) {
//   long double *value = calloc(1, sizeof(float));
//   char *endpoint;
//   verify_memory(value);
//   *value = strtold(text, &endpoint);
//   fauxy_bit_value(bit).as_long_float = value;
//
//   printf("%Lf %Lf\n", *value, *fauxy_bit_value(bit).as_long);
//   return true;
// error:
//   return false;
// }

Boolean fauxy_bit_add_string_value(FauxyBit *bit, char *text) {
  char *value = calloc(strlen(text) + 1, sizeof(char));
  verify_memory(value);
  strcpy(value, text);
  fauxy_bit_value(bit) = value;

  return true;
error:
  return false;
}

void fauxy_bit_free(FauxyBit *bit) {
  int type = fauxy_bit_type(bit);

  fx_pfree(fauxy_bit_value(bit));

  // if (type == FX_BIT_FLOAT) {
  //   fx_pfree(fauxy_bit_float__value(bit));
  // } else if (type == FX_BIT_SHORT) {
  //   fx_pfree(fauxy_bit_short__value(bit));
  // } else if (type == FX_BIT_LONG) {
  //   fx_pfree(fauxy_bit_long__value(bit));
  // } else {
  //   fx_pfree(fauxy_bit_string__value(bit));
  // }

  fx_pfree(bit);
}
