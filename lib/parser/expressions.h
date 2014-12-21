#ifndef __fauxy_expression
#define __fauxy_expression 1

#include <stdlib.h>

#include "../bricks/array.h"
#include "object.h"

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
  int token_type; // for lookups and literals
  FxExpressions *value;
} FxExpression;

#define fx_expression_type(E)        ((E)->type)
#define fx_expression_token_type(E)  ((E)->token_type)
#define fx_expression_value(E)       ((E)->value)

FxExpression *FxExpression_create(int type, int token_type);
FxExpression *FxExpression_convert_literal(FxParseObject *bit_wrapper, int token_type);
void          fx_expression_free(FxExpression *expression);

#endif
