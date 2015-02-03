#include <string.h>

#include "bit.h"

#include "../bricks/helpers.h"
#include "../bricks/string.h"
#include "../bricks/json_gen.h"

FxP_Bit *FxP_Bit_string_create(char *text) {
  FxP_Bit *bit = fx_alloc(FxP_Bit);
  verify_memory(bit);

  fxp_bit_type(bit) = FX_BIT_STRING;

  char *unwrapped = NULL;
  char c = text[0];
  if (c == '\'' || c == '"') {
    unwrapped = fx_trim_quote_char_text(text);
    verify(unwrapped);
  }
  FxB_String *value = FxB_String_create(unwrapped ? unwrapped : text);
  fxp_bit_value(bit) = value;

  if (unwrapped) { fx_pfree(unwrapped); }
  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

FxP_Bit *FxP_Bit_integer_create(char *text) {
  FxP_Bit *bit = fx_alloc(FxP_Bit);
  verify_memory(bit);

  fxp_bit_type(bit) = FX_BIT_NUMBER;

  FxB_Number *value = FxB_Integer_from_string(text);
  verify(value);

  fxp_bit_value(bit) = value;

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

FxP_Bit *FxP_Bit_decimal_create(char *text) {
  FxP_Bit *bit = fx_alloc(FxP_Bit);
  verify_memory(bit);

  fxp_bit_type(bit) = FX_BIT_NUMBER;

  FxB_Number *value = FxB_Decimal_from_string(text);
  verify(value);

  fxp_bit_value(bit) = value;

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

FxP_Bit *FxP_Bit_exponent_create(char *text) {
  FxP_Bit *bit = fx_alloc(FxP_Bit);
  verify_memory(bit);

  fxp_bit_type(bit) = FX_BIT_NUMBER;

  FxB_Number *value = FxB_Exponent_from_string(text);
  verify(value);

  fxp_bit_value(bit) = value;

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}

char *fx_trim_quote_char_text(char *text) {
  int length = strlen(text) - 2;
  char *value = calloc(length + 1, sizeof(char));
  verify_memory(value);

  int i;
  for(i = 0; i < length; i++) {
    value[i] = text[i+1];
  }

  return value;
error:
  return NULL;
}

void fxp_bit_free(FxP_Bit *bit) {
  fx_pfree(fxp_bit_value(bit));
  fx_pfree(bit);
}

FxB_String *fxp_bit_value_description(FxP_Bit *bit) {
  int type = fxp_bit_type(bit);
  char str[16] = "";
  FxB_String *string;

  if (type == FX_BIT_NUMBER) {
    string = fxb_number_inspect(fxp_bit_number__value(bit));
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

    string = FxB_String_create(str);
  }
  verify_memory(string);

  return string;
error:
  return NULL;
}

FxB_String *fxp_bit_type_description(FxP_Bit *bit) {
  int type = fxp_bit_type(bit);
  FxB_String *string;

  if (type == FX_BIT_NUMBER) {
    string = fxb_number_type_description(fxp_bit_number__value(bit));
  } else {
    string = FxB_String_create("STRING");
  }

  return string;
}

FxB_String *fxp_bit_inspect(FxP_Bit *bit) {
  FxB_String *bit_key = NULL;
  FxB_String *bit_value = NULL;
  FxB_String *pair = NULL;
  FxB_String *json = NULL;
  FxB_Array *pairs = NULL;

  bit_key = fxp_bit_type_description(bit);
  verify(bit_key);
  bit_value = fxp_bit_value_description(bit);
  verify(bit_value);

  pair = fxb_json_gen_bald_pair(bit_key, bit_value);
  verify(pair);

  pairs = FxB_Array_create(1);
  verify(pairs);
  fxb_array_push(pairs, pair);

  json = fxb_json_gen_wrap_pairs(pairs);
  verify(json);

  fxb_string_free(bit_key);
  fxb_string_free(bit_value);
  fxb_string_free(pair);
  fxb_array_free(pairs);

  return json;
error:
  if (bit_key) { fxb_string_free(bit_key); }
  if (bit_value) { fxb_string_free(bit_value); }
  if (pair) { fxb_string_free(pair); }
  if (pairs) { fxb_array_free(pairs); }
  return NULL;
}
