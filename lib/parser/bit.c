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
  int type = fxp_bit_type(bit);
  json_t *root = NULL;
  FxB_String *bit_value = NULL;
  FxB_Number *number = NULL;

  FxB_String *bit_key = fxp_bit_type_description(bit);
  verify(bit_key);
  root = json_object();

  if (type == FX_BIT_NUMBER) {
    number = fxp_bit_number__value(bit);

    if (fxb_number_type(number) == FX_INT_SHORT) {
      json_object_set_new(root, fxb_string_value(bit_key), json_integer(fxb_number_value_short(number)));
    } else if (fxb_number_type(number) == FX_INT_STANDARD) {
      json_object_set_new(root, fxb_string_value(bit_key), json_integer(fxb_number_value_standard(number)));
    } else if (fxb_number_type(number) == FX_INT_LONG) {
      json_object_set_new(root, fxb_string_value(bit_key), json_integer(fxb_number_value_long(number)));
    } else {
      json_object_set_new(root, fxb_string_value(bit_key), json_real(fxb_number_value_double(number)));
    }
  } else {
    json_object_set_new(root, fxb_string_value(bit_key), json_string(fxp_bit_string_value(bit)));
  }

  FxB_String *json = FxB_String_create(generate_json_chars(root));
  verify(json);

  json_decref(root);
  fxb_string_free(bit_key);
  if (bit_value) { fxb_string_free(bit_value); }

  return json;
error:
  if (bit_key) { fxb_string_free(bit_key); }
  if (bit_value) { fxb_string_free(bit_value); }
  if (root) { json_decref(root); }
  return NULL;
}
