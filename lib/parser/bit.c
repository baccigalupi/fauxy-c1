#include <string.h>

#include "bit.h"

#include "../bricks/helpers.h"
#include "../bricks/string.h"

FxP_Bit *FxP_Bit_create(int token_type, char *text) {
  FxP_Bit *bit = fx_alloc(FxP_Bit);
  verify_memory(bit);

  int size = strlen(text);
  int type = FxP_Bit_bit_type(token_type, fxp_bit_size_is_small(size));
  fxp_bit_type(bit) = type;
  fxp_bit_size(bit) = size;

  Boolean success;
  if (type == FX_BIT_FLOAT) {
    success = fxp_bit_add_float_value(bit, text);
  } /* else if (type == FX_BIT_LONG_FLOAT) {
    success = fxp_bit_add_long_float_value(bit, text);
  } */ else if (type == FX_BIT_SHORT) {
    success = fxp_bit_add_short_value(bit, text);
  } else if (type == FX_BIT_LONG) {
    success = fxp_bit_add_long_value(bit, text);
  } else {
    // little wonky to have this here, maybe should switch up and
    // do this work when a literal statement is defined, not here
    if (text[0] == '\'' || text[0] == '"') {
      success = fx_trim_string_value(bit, text);
    } else {
      success = fxp_bit_add_string_value(bit, text);
    }
  }
  verify(success);

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

int FxP_Bit_bit_type(int token_type, Boolean is_small) {
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

inline Boolean fxp_bit_add_short_value(FxP_Bit *bit, char *text) {
  short *value = calloc(1, sizeof(short));
  verify_memory(value);
  *value = atoi(text);
  fxp_bit_value(bit) = value;

  return true;
error:
  return false;
}

Boolean fxp_bit_add_long_value(FxP_Bit *bit, char *text) {
  long long *value = calloc(1, sizeof(long long));
  verify_memory(value);
  char *endpoint;
  *value = strtoll(text, &endpoint, 10);
  fxp_bit_value(bit) = value;


  return true;
error:
  return false;
}

Boolean fxp_bit_add_float_value(FxP_Bit *bit, char *text) {
  double *value = calloc(1, sizeof(float));
  verify_memory(value);
  *value = atof(text);
  fxp_bit_value(bit) = value;

  return true;
error:
  return false;
}

// Boolean fxp_bit_add_long_float_value(FxP_Bit *bit, char *text) {
//   long double *value = calloc(1, sizeof(float));
//   char *endpoint;
//   verify_memory(value);
//   *value = strtold(text, &endpoint);
//   fxp_bit_value(bit).as_long_float = value;
//
//   printf("%Lf %Lf\n", *value, *fxp_bit_value(bit).as_long);
//   return true;
// error:
//   return false;
// }

Boolean fx_trim_string_value(FxP_Bit *bit, char *text) {
  int length = strlen(text) - 2;
  char *value = calloc(length + 1, sizeof(char));
  verify_memory(value);

  int i;
  for(i = 0; i < length; i++) {
    value[i] = text[i+1];
  }
  fxp_bit_value(bit) = value;

  return true;
error:
  return false;
}

Boolean fxp_bit_add_string_value(FxP_Bit *bit, char *text) {
  int length = strlen(text);
  char *value = calloc(length + 1, sizeof(char));
  verify_memory(value);

  strcpy(value, text);
  fxp_bit_value(bit) = value;

  return true;
error:
  return false;
}

void fxp_bit_free(FxP_Bit *bit) {
  fx_pfree(fxp_bit_value(bit));
  fx_pfree(bit);
}

String *fxp_bit_value_inspect(FxP_Bit *bit) {
  int type = fxp_bit_type(bit);
  char str[16] = "";
  String *string;

  if (type == FX_BIT_FLOAT) {
    sprintf(str, "%.2f", fxp_bit_float_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_LONG_FLOAT) {
    sprintf(str, "%.1e", fxp_bit_float_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_SHORT) {
    sprintf(str, "%d", fxp_bit_short_value(bit));
    string = String_create(str);
  } else if (type == FX_BIT_LONG) {
    sprintf(str, "%.1e", (float)fxp_bit_long_value(bit));
    string = String_create(str);
  } else {
    char *bit_string = fxp_bit_string_value(bit);
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

String *fxp_bit_type_inspect(FxP_Bit *bit) {
  int type = fxp_bit_type(bit);
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

String *fxp_bit_inspect(FxP_Bit *bit) {
  int type = fxp_bit_type(bit);
  String *string = String_create_with_capacity(32);
  verify_memory(string);
  String *value = fxp_bit_value_inspect(bit);
  verify_memory(value);

  string_push_char(string, '<');
  if (type == FX_BIT_FLOAT || type == FX_BIT_LONG_FLOAT) {
    string_add_chars(string, "FLOAT");
  } else if (type == FX_BIT_SHORT || type == FX_BIT_LONG) {
    string_add_chars(string, "INTEGER");
  } else {
    string_add_chars(string, "STRING");
  }
  string_add_chars(string, ": ");
  string_add_string(string, value);
  string_push_char(string, '>');

  string_free(value);

  return string;
error:
  if (string) { string_free(string); }
  return NULL;
}
