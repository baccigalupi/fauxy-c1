#include "bit.h"

#include "../bricks/bricks.h"
#include "../bricks/error_handling.h"
#include "../parser/parse.tab.h"
#include "../bricks/string.h"


FauxyBit *FauxyBit_create(int token_type, char *text) {
  FauxyBit *bit = fx_alloc(FauxyBit);
  int type;

  if (token_type == TOKEN_FLOAT) {
    type = FX_BIT_FLOAT;
    FauxyBitFloat *value = fx_alloc(FauxyBitFloat);
    check_mem(value);
    value->value = atof(text);
    bit->type = type;
    bit->value = value;
  } else if (token_type == TOKEN_INTEGER) {
    type = FX_BIT_INTEGER;
    FauxyBitInteger *value = fx_alloc(FauxyBitInteger);
    check_mem(value);
    value->value = atoi(text);
    bit->type = type;
    bit->value = value;
  } else {
    type = FX_BIT_STRING;
    String *value = String_create(text);
    check_mem(value);
    bit->type = type;
    bit->value = value;
  }

  return bit;
error:
  if (bit) { fx_pfree(bit); }
  return NULL;
}
