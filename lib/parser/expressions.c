#include "../bricks/helpers.h"
#include "expressions.h"

FxExpression *FxExpression_create(int type) {
  FxExpression *expression = fx_alloc(FxExpression);
  verify_memory(expression);

  FxExpressions *value = FxExpressions_create();
  verify_memory(value);

  fx_expression_type(expression) = type;
  fx_expression_value(expression) = value;

  return expression;
error:
  if (expression) { fx_pfree(expression); }
  return NULL;
}

void fx_expression_free(FxExpression *expression) {
  fx_expressions_free(fx_expression_value(expression));
  fx_pfree(expression);
}

FxExpression *FxLiteral_create(FxBit *bit, int token_type) {
  FxExpression *literal = FxExpression_create(FX_ST_LITERAL);
  verify_memory(literal);

  FxExpressions *values = fx_expression_value(literal);
  int *type = fx_alloc(int);
  *type = token_type;
  fx_expressions_push(values, type);
  fx_expressions_push(values, bit);

  return literal;
error:
  return NULL;
}

void fx_literal_free(FxLiteral *literal) {
  fx_bit_free(fx_literal_bit(literal));
  fx_pfree(fx_literal__type(literal));
  array_free(fx_expression_value(literal));
  fx_pfree(literal);
}

String *fx_literal_description(FxLiteral *literal) {
  char str[24];

  if (fx_literal_type(literal) == TOKEN_STRING) {
    strcpy(str, "String");
  } else if (fx_literal_type(literal) == TOKEN_EVAL_STRING) {
    strcpy(str, "String.Evaluable");
  } else if (fx_literal_type(literal) == TOKEN_REGEX) {
    strcpy(str, "Regex");
  } else if (fx_literal_type(literal) == TOKEN_SYMBOL) {
    strcpy(str, "Symbol");
  } else if (fx_literal_type(literal) == TOKEN_INTEGER) {
    strcpy(str, "Integer");
  } else {
    strcpy(str, "Float");
  }

  String *description = String_create(str);
  verify_memory(description);

  return description;
error:
  return NULL;
}

String *fx_literal_inspect(FxLiteral *literal) {
  String *bit = fx_bit_inspect(fx_literal_bit(literal));
  verify(bit);
  String *description = fx_literal_description(literal);
  verify(bit);
  String *inspection = String_create_with_capacity(128);
  verify_memory(inspection);

  // TODO: verify return values of all string operations

  string_concat(inspection, "(literal: ");
  string_add(inspection, description);
  string_concat(inspection, ", ");
  string_add(inspection, bit);
  string_push(inspection, ')');

  string_free(description);
  string_free(bit);

  return inspection;
error:
  return NULL;
}
