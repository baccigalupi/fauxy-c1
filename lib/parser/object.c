#include "../bricks/helpers.h"
#include "object.h"

FxParseObject *FxParseObject_create_bit(int token_type, char *text) {
  FxParseObject *object = fx_alloc(FxParseObject);
  verify_memory(object);

  FxBit *bit = FxBit_create(token_type, text);
  verify_memory(object);

  fx_parse_object_type(object) = FX_O_BIT;
  fx_parse_object_value(object) = bit;

  return object;
error:
  if (object) { fx_pfree(object); }
  return NULL;
}

void fx_parse_object_free(FxParseObject *object) {
  if (fx_parse_object_type(object) == FX_O_BIT) {
    fx_bit_free(fx_parse_object_value(object));
  } else {
    fx_expression_free(fx_parse_object_value(object));
  }

  fx_pfree(object);
}

String *fx_parse_object_inspect(FxParseObject *object) {
  String *inspection = NULL;
  if (fx_parse_object_type(object) == FX_O_BIT) {
    inspection = fx_bit_inspect(fx_parse_object_value(object));
  } else {
    // build the exprssion inspection
  }
  return inspection;
}
