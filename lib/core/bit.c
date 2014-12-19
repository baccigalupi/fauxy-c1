#include <string.h>

#include "bit.h"

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
  fx_pfree(fauxy_bit_value(bit));
  fx_pfree(bit);
}

String *fauxy_bit_value_inspect(FauxyBit *bit) {
  int type = fauxy_bit_type(bit);
  char str[16] = "";
  String *string;

  if (type == FX_BIT_FLOAT) {
    sprintf(str, "%.2f", fauxy_bit_float_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_LONG_FLOAT) {
    sprintf(str, "%.1e", fauxy_bit_float_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_SHORT) {
    sprintf(str, "%d", fauxy_bit_short_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_LONG) {
    sprintf(str, "%.1e", (float)fauxy_bit_long_value(bit));
    string = String_create(str);
  } else {
    str[0] = '"';
    char *bit_string = fauxy_bit_string_value(bit);
    int length;
    if (strlen(bit_string) > 10) {
      // "hello worl..."\0
      strncpy(str, bit_string, 10);
      length = strlen(str);
      str[length] = str[length+1] = str[length+2] = '.';
      length += 3;
    } else {
      strcpy(str, bit_string);
      length = strlen(str);
    }
    str[length] = '"';
    str[length+1] = '\0';

    string = String_create(str);
  }
  verify_memory(string);

  return string;
error:
  return NULL;
}

String *fauxy_bit_type_inspect(FauxyBit *bit) {
  int type = fauxy_bit_type(bit);
  String *string;

  if (type == FX_BIT_FLOAT || type == FX_BIT_LONG_FLOAT) {
    string = String_create("FLOAT");
  } else if (type == FX_BIT_SHORT || type == FX_BIT_LONG) {
    string = String_create("FLOAT");
  } else {
    string = String_create("STRING");
  }

  verify_memory(string);

  return string;
error:
  return NULL;
}

String *fauxy_bit_inspect(FauxyBit *bit) {
  int type = fauxy_bit_type(bit);
  String *string = String_create_with_capacity(32);
  verify_memory(string);
  String *value = fauxy_bit_value_inspect(bit);
  verify_memory(value);

  string_push(string, '<');
  if (type == FX_BIT_FLOAT || type == FX_BIT_LONG_FLOAT) {
    string_concat(string, "FLOAT");
  } else if (type == FX_BIT_SHORT || type == FX_BIT_LONG) {
    string_concat(string, "INTEGER");
  } else {
    string_concat(string, "STRING");
  }
  string_concat(string, ": ");
  string_add(string, value);
  string_push(string, '>');

  string_free(value);

  return string;
error:
  if (string) { string_free(string); }
  return NULL;
}
