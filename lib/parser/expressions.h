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

FxExpression *FxTypedExpression_create(FxBit *bit, int type, int token_type);
String       *fx_typed_expression_inspect(FxExpression *expression, String *description, String *preface);

// Literals have value array [token_type, bit]
typedef FxExpression FxLiteral;
#define fx_literal__type(E)           (array_get(fx_expression_value(E), 0))
#define fx_literal_type(E)            (*((int *)fx_literal__type(E)))
#define fx_literal_bit(E)             (FxBit *)(array_get(fx_expression_value(E), 1))

FxLiteral *FxLiteral_create(FxBit *bit, int token_type);
String    *fx_literal_inspect(FxLiteral *literal);
String    *fx_literal_description(FxLiteral *literal);
void       fx_literal_free(FxLiteral *literal);

// Lookups are similar to literal, with value array [token_type, bit]
typedef FxExpression FxLookup;
#define fx_lookup__type(E)           (array_get(fx_expression_value(E), 0))
#define fx_lookup_type(E)            (*((int *)fx_lookup__type(E)))
#define fx_lookup_bit(E)             (FxBit *)(array_get(fx_expression_value(E), 1))
#define fx_lookup_free(E)            fx_literal_free(E)

FxLookup  *FxLookup_create(FxBit *bit, int token_type);
String    *fx_lookup_inspect(FxLookup *literal);
String    *fx_lookup_description(FxLookup *literal);

// Block value array [arguments, statements]
typedef FxExpression FxBlock;
#define fx_block_arguments(E)     (FxExpression *)(array_get(fx_expression_value(E), 0))
#define fx_block_expressions(E)   (FxExpressions *)(array_get(fx_expression_value(E), 1))

#endif
