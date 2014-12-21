#include "../bricks/helpers.h"
#include "expressions.h"

FxExpression *FxExpression_create(int type, int token_type) {
  FxExpression *expression = fx_alloc(FxExpression);
  verify_memory(expression);

  FxExpressions *value = FxExpressions_create();
  verify_memory(value);

  fx_expression_type(expression) = type;
  fx_expression_token_type(expression) = token_type;
  fx_expression_value(expression) = value;

  return expression;
error:
  if (expression) { fx_pfree(expression); }
  return NULL;
}


FxExpression *FxExpression_convert_literal(FxBit *bit, int token_type) {
  FxExpression *expression = FxExpression_create(FX_ST_LITERAL, token_type);
  verify_memory(expression);

  FxExpressions *set = fx_expression_value(expression);
  fx_expressions_push(set, bit);

  return expression;
error:
  return NULL;
}

void fx_expression_free(FxExpression *expression) {
  fx_expressions_free(fx_expression_value(expression));
  fx_pfree(expression);
}
