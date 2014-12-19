#ifndef __fauxy_expression
#define __fauxy_expression 1

#include <stdlib.h>

#include "../bricks/array.h"

enum {
  FX_ST_LITERAL = 350,
  FX_ST_LOOKUP,
  FX_ST_BLOCK,
  FX_ST_LIST,
  FX_ST_ARGS,
  FX_ST_GROUPED,
  FX_ST_METHOD,
  FX_ST_LOCAL_ASSIGN,
  FX_ST_ATTR_ASSIGN,
  FX_ST_EXPORT
};

typedef Array FxExpressions;
#define FxExpressions_create Array_create
#define fx_expressions_free  array_free

typedef struct FxExpression {
  int type;
  FxExpressions *value;
} FxExpression;



#endif
