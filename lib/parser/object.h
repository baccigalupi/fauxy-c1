#ifndef __fx_parse_object
#define __fx_parse_object 1

#include "../bit.h"
#include "../expressions.bit.h"

typedef struct FxParseObject {
  int type;
  void *value;
} FxParseObject;

#define fx_parse_object_type(F)         ((F)->type)
#define fx_parse_object_value(F)        ((F)->value)
#define fx_parse_object_bit(F)          (FauxyBit *)((F)->value)
#define fx_parse_object_expression(F)   (FxExpression *)((F)->value)

#endif
