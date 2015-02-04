#include "literal.h"
#include "../parser/expression_inspect.h"

char *fxi_literal_key(FxP_Literal *literal) {
  FxP_Bit *bit = fxp_literal_bit(literal);
  int bit_size = 0;
  FxB_String *bit_description;
  if (bit) {
    if (fxp_bit_type(bit) == FX_BIT_NUMBER) {
      if (fxb_number_is_decimal(fxp_bit_number__value(bit))) {
        return NULL;
      } else {
        bit_description = fxb_number_full_inspect(fxp_bit_number__value(bit));
      }
    } else {
      bit_description = fxp_bit_string__value(bit);
    }
    bit_size = fxb_string_length(bit_description);
  }

  int type = fxp_literal_type(literal);
  char *key = calloc(bit_size + 5, sizeof(char));
  sprintf(key, "%d", type);
  if (bit) {
    strcat(key, "-");
    strcat(key, fxb_string_value(bit_description));
  }

  if (bit && fxp_bit_type(bit) == FX_BIT_NUMBER) {
    fxb_string_free(bit_description);
  }

  return key;
error:
  return NULL;
}

