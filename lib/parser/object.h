#ifndef __fx_parse_object
#define __fx_parse_object 1

#include "bit.h"
#include "expressions.h"

enum {
  FX_O_BIT,
  FX_O_EXPRESSION
};

typedef struct FxParseObject {
  int type;
  void *value;
} FxParseObject;

#define fx_parse_object_type(F)         ((F)->type)
#define fx_parse_object_value(F)        ((F)->value)
#define fx_parse_object_bit(F)          (FxBit *)((F)->value)
#define fx_parse_object_expression(F)   (FxExpression *)((F)->value)

#endif
