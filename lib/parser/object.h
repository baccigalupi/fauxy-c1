#ifndef __fx_parse_object
#define __fx_parse_object 1

enum {
  FX_O_BIT = 310,
  FX_O_EXPRESSION
};

typedef struct FxParseObject {
  int type;
  void *value;
} FxParseObject;

#include "bit.h"
#include "expressions.h"

#define fx_parse_object_type(F)         ((F)->type)
#define fx_parse_object_value(F)        ((F)->value)
#define fx_parse_object_bit(F)          (FxBit *)((F)->value)
#define fx_parse_object_expression(F)   (FxExpression *)((F)->value)

FxParseObject *FxParseObject_create_bit(int token_type, char *text);
void           fx_parse_object_free(FxParseObject *object);
String        *fx_parse_object_inspect(FxParseObject *object);

#endif
