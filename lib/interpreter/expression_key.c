#include "expression_key.h"

#include "../parser/expression_inspect.h"

char *fxi_type_key(FxP_Expression *expression) {
  int type = fxp_literal_type(expression);
  char *key = calloc(4, sizeof(char));
  verify_memory(key);
  sprintf(key, "%d", type);
  return key;
error:
  return NULL;
}

char *fxi_literal_key(FxP_Literal *literal) {
  FxP_Bit *bit = fxp_literal_bit(literal);
  if (bit && fxb_number_is_decimal(fxp_bit_number__value(bit))) { return NULL; }

  FxB_String *key = NULL;

  char *key_type = fxi_type_key(literal);
  verify(key_type);

  if (!bit) { return key_type; }

  int bit_size = 0;
  FxB_String *bit_description;

  if (fxp_bit_type(bit) == FX_BIT_NUMBER) {
    bit_description = fxb_number_full_inspect(fxp_bit_number__value(bit));
  } else {
    bit_description = fxp_bit_string__value(bit);
  }
  bit_size = fxb_string_length(bit_description);

  key = FxB_String_create(key_type);
  verify(key);
  fxb_string_push_char(key, '-');
  fxb_string_add_string(key, bit_description);

  if (fxp_bit_type(bit) == FX_BIT_NUMBER) {
    fxb_string_free(bit_description);
  }
  fx_pfree(key_type);

  char *_key = fxb_string_value(key);
  fx_pfree(key); // don't free the value, just the husk

  return _key;
error:
  if (key) { fx_pfree(key); }
  return NULL;
}

char *fxi_lookup_key(FxP_Lookup *lookup) {
  FxB_String *key = NULL;
  char *key_type = NULL;
  FxB_String *bit_description = NULL;

  FxP_Bit *bit = fxp_lookup_bit(lookup);
  verify(bit);

  bit_description = fxp_bit_string__value(bit);
  verify(bit_description);

  key_type = fxi_type_key(lookup);

  key = FxB_String_create(key_type);
  verify(key);
  verify(fxb_string_push_char(key, '-'));
  verify(fxb_string_add_string(key, bit_description));

  char *_key = fxb_string_value(key);

  fxb_string_free(key);
  fx_pfree(key_type);

  return _key;
error:
  if (key)             { fxb_string_free(key); }
  if (key_type)        { fx_pfree(key_type); }
  return NULL;
}
