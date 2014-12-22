#include <string.h>

#include "bit.h"

#include "../bricks/helpers.h"
#include "../bricks/string.h"


FxBit *FxBit_create(int token_type, char *text) {
  FxBit *bit = fx_alloc(FxBit);
  verify_memory(bit);

  int size = strlen(text);
  int type = FxBit_bit_type(token_type, fx_bit_size_is_small(size));
  fx_bit_type(bit) = type;
  fx_bit_size(bit) = size;

  Boolean success;
  if (type == FX_BIT_FLOAT) {
    success = fx_bit_add_float_value(bit, text);
  } /* else if (type == FX_BIT_LONG_FLOAT) {
    success = fx_bit_add_long_float_value(bit, text);
  } */ else if (type == FX_BIT_SHORT) {
    success = fx_bit_add_short_value(bit, text);
  } else if (type == FX_BIT_LONG) {
    success = fx_bit_add_long_value(bit, text);
  } else {
    success = fx_bit_add_string_value(bit, text);
  }
  verify(success);

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

int FxBit_bit_type(int token_type, Boolean is_small) {
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

inline Boolean fx_bit_add_short_value(FxBit *bit, char *text) {
  short *value = calloc(1, sizeof(short));
  verify_memory(value);
  *value = atoi(text);
  fx_bit_value(bit) = value;

  return true;
error:
  return false;
}

Boolean fx_bit_add_long_value(FxBit *bit, char *text) {
  long long *value = calloc(1, sizeof(long long));
  verify_memory(value);
  char *endpoint;
  *value = strtoll(text, &endpoint, 10);
  fx_bit_value(bit) = value;


  return true;
error:
  return false;
}

Boolean fx_bit_add_float_value(FxBit *bit, char *text) {
  double *value = calloc(1, sizeof(float));
  verify_memory(value);
  *value = atof(text);
  fx_bit_value(bit) = value;

  return true;
error:
  return false;
}

// Boolean fx_bit_add_long_float_value(FxBit *bit, char *text) {
//   long double *value = calloc(1, sizeof(float));
//   char *endpoint;
//   verify_memory(value);
//   *value = strtold(text, &endpoint);
//   fx_bit_value(bit).as_long_float = value;
//
//   printf("%Lf %Lf\n", *value, *fx_bit_value(bit).as_long);
//   return true;
// error:
//   return false;
// }

Boolean fx_bit_add_string_value(FxBit *bit, char *text) {
  char *value = calloc(strlen(text) + 1, sizeof(char));
  verify_memory(value);
  strcpy(value, text);
  fx_bit_value(bit) = value;

  return true;
error:
  return false;
}

void fx_bit_free(FxBit *bit) {
  fx_pfree(fx_bit_value(bit));
  fx_pfree(bit);
}

String *fx_bit_value_inspect(FxBit *bit) {
  int type = fx_bit_type(bit);
  char str[16] = "";
  String *string;

  if (type == FX_BIT_FLOAT) {
    sprintf(str, "%.2f", fx_bit_float_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_LONG_FLOAT) {
    sprintf(str, "%.1e", fx_bit_float_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_SHORT) {
    sprintf(str, "%d", fx_bit_short_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_LONG) {
    sprintf(str, "%.1e", (float)fx_bit_long_value(bit));
    string = String_create(str);
  } else {
    char *bit_string = fx_bit_string_value(bit);
    int  bit_length = strlen(bit_string);
    int  copy_length = bit_length > 10 ? 10 : bit_length;
    int  ending_i =    bit_length > 10 ? 14 : bit_length + 1;
    int  i;

    str[0] = '"';
    for (i = 0; i < copy_length; i++) {
      str[i+1] = bit_string[i];
    }
    if (bit_length != copy_length) {
      str[11] = str[12] = str[13] = '.';
    }
    str[ending_i] = '"';

    string = String_create(str);
  }
  verify_memory(string);

  return string;
error:
  return NULL;
}

String *fx_bit_type_inspect(FxBit *bit) {
  int type = fx_bit_type(bit);
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

String *fx_bit_inspect(FxBit *bit) {
  int type = fx_bit_type(bit);
  String *string = String_create_with_capacity(32);
  verify_memory(string);
  String *value = fx_bit_value_inspect(bit);
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
