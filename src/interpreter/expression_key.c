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

// TODO: move to expression eval and rename fxi_copy_lookup_key
char *fxi_lookup_key(FxP_Lookup *lookup) {
  char *key = NULL;
  char *original_key = NULL;
  FxP_Bit *bit = fxp_lookup_bit(lookup);
  verify(bit);

  original_key = fxp_bit_string_value(bit);
  verify(original_key);

  key = calloc(strlen(original_key) + 1, sizeof(char));
  strcpy(key, original_key);

  return key;
error:
  return NULL;
}
