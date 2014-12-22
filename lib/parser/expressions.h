#ifndef __fauxy_expression
#define __fauxy_expression 1

#include <stdlib.h>

#include "../bricks/string.h"
#include "../bricks/array.h"
#include "bit.h"

#define FX_EXPRESSION_INITAL_SIZE 5

enum {
  FX_ST_LITERAL = 320,
  FX_ST_LOOKUP,
  FX_ST_BLOCK,
  FX_ST_LIST,
  FX_ST_ARGS,
  FX_ST_GROUPED,
  FX_ST_METHOD,
  FX_ST_LOCAL_ASSIGN,
  FX_ST_ATTR_ASSIGN,
  FX_ST_EXPORT
}; // statement types

typedef Array FxExpressions;
#define FxExpressions_create()      Array_create(FX_EXPRESSION_INITAL_SIZE)
#define fx_expressions_free(E)      array_free(E)
#define fx_expressions_push(E, V)   array_push(E, V)

typedef struct FxExpression {
  int type;
  FxExpressions *value;
} FxExpression;

#define fx_expression_type(E)        ((E)->type)
#define fx_expression_value(E)       ((E)->value)

FxExpression *FxExpression_create(int type);
void          fx_expression_free(FxExpression *expression);

// Literals have value array [token_type, bit]
typedef FxExpression FxLiteral;
#define fx_literal__type(E)           (array_get(fx_expression_value(E), 0))
#define fx_literal_type(E)            (*((int *)fx_literal__type(E)))
#define fx_literal_bit(E)             (FxBit *)(array_get(fx_expression_value(E), 1))

FxLiteral *FxLiteral_create(FxBit *bit, int token_type);
String    *fx_literal_inspect(FxLiteral *literal);
String    *fx_literal_description(FxLiteral *literal);
void      fx_literal_free(FxLiteral *literal);

#endif
