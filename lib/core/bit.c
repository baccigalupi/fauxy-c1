#include "bit.h"

#include "../parser/parse.tab.h"

#include "../bricks/bricks.h"
#include "../bricks/helpers.h"
#include "../bricks/string.h"


FauxyBit *FauxyBit_create(int token_type, char *text) {
  FauxyBit *bit = fx_alloc(FauxyBit);
  int type;

  if (token_type == TOKEN_FLOAT) {
    type = FX_BIT_FLOAT;
    FauxyBitFloat *value = fx_alloc(FauxyBitFloat);
    verify_memory(value);
    value->value = atof(text);
    bit->type = type;
    bit->value = value;
  } else if (token_type == TOKEN_INTEGER) {
    type = FX_BIT_INTEGER;
    FauxyBitInteger *value = fx_alloc(FauxyBitInteger);
    verify_memory(value);
    value->value = atoi(text);
    bit->type = type;
    bit->value = value;
  } else {
    type = FX_BIT_STRING;
    String *value = String_create(text);
    verify_memory(value);
    bit->type = type;
    bit->value = value;
  }

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}
