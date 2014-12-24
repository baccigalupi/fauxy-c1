#include "../bricks/helpers.h"
#include "expressions.h"

FxExpression *FxExpression_create(int type) {
  FxExpression *expression = fx_alloc(FxExpression);
  verify_memory(expression);

  Array *value = Array_create(4);
  verify_memory(value);

  fx_expression_type(expression) = type;
  fx_expression_value(expression) = value;

  return expression;
error:
  if (expression) { fx_pfree(expression); }
  return NULL;
}

void fx_expression_free(FxExpression *expression) {
  array_free(fx_expression_value(expression));
  fx_pfree(expression);
}

FxExpressions *FxExpressions_create() {
  FxExpression *expressions = FxExpression_create(FX_ST_EXPRESSIONS);
  verify(expressions);
  return expressions;
error:
  return NULL;
}

void fx_expressions_free(FxExpressions *expressions) {
  // TODO: case for each type of statement
}

FxExpression *FxTypedExpression_create(FxBit *bit, int exp_type, int token_type) {
  FxExpression *expression = FxExpression_create(exp_type);
  verify_memory(expression);

  Array *values = fx_expression_value(expression);
  int *type = fx_alloc(int);
  *type = token_type;
  array_push(values, type);
  array_push(values, bit);

  return expression;
error:
  return NULL;
}

FxExpression *FxLiteral_create(FxBit *bit, int token_type) {
  FxExpression *literal = FxTypedExpression_create(bit, FX_ST_LITERAL, token_type);
  verify(literal);
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
  } else if (fx_literal_type(literal) == TOKEN_FLOAT) {
    strcpy(str, "Float");
  } else if (fx_literal_type(literal) == TOKEN_NIL) {
    strcpy(str, "Nil");
  } else if (fx_literal_type(literal) == TOKEN_TRUE) {
    strcpy(str, "True");
  } else if (fx_literal_type(literal) == TOKEN_FALSE) {
    strcpy(str, "False");
  }

  String *description = String_create(str);
  verify_memory(description);

  return description;
error:
  return NULL;
}

String *fx_typed_expression_inspect(FxExpression *expression, String *description, String *preface) {
  String *bit;
  if (fx_literal_bit(expression)) {
    bit = fx_bit_inspect(fx_literal_bit(expression));
  } else {
    bit = String_create_with_capacity(1);
  }
  verify(bit);
  String *inspection = String_create_with_capacity(128);
  verify_memory(inspection);

  // TODO: verify return values of all string operations

  string_add(inspection, preface);
  string_add(inspection, description);
  if (string_length(bit)) {
    string_concat(inspection, ", ");
  }
  string_add(inspection, bit);
  string_push(inspection, ')');

  string_free(description);
  string_free(preface);
  string_free(bit);

  return inspection;
error:
  return NULL;
}

String *fx_literal_inspect(FxLiteral *literal) {
  String *preface = String_create("(literal: ");
  verify(preface);

  String *description = fx_literal_description(literal);
  verify(description);

  String *inspection = fx_typed_expression_inspect(literal, description, preface);
  return inspection;
error:
  return NULL;
}

FxLookup *FxLookup_create(FxBit *bit, int token_type) {
  FxExpression *lookup = FxTypedExpression_create(bit, FX_ST_LOOKUP, token_type);
  verify(lookup);

  return lookup;
error:
  return NULL;
}

String *fx_lookup_inspect(FxLookup *lookup) {
  String *preface = String_create("(lookup: ");
  String *description = fx_lookup_description(lookup);
  verify(preface);
  verify(description);

  String *inspection = fx_typed_expression_inspect(lookup, description, preface);
  return inspection;
error:
  return NULL;
}

String *fx_lookup_description(FxLookup *lookup) {
  char str[24];

  if (fx_lookup_type(lookup) == TOKEN_ID) {
    strcpy(str, "Identifier");
  } else {
    strcpy(str, "Class Identifier");
  }

  String *description = String_create(str);
  verify_memory(description);

  return description;
error:
  return NULL;
}

FxMethodCall *FxMethodCall_create_implicit(FxBit *method_name, FxExpression *argument) {
  FxMethodCall *call = FxMethodCall_create();
  verify_memory(call);

  fx_method_set_message(call, method_name);
  fx_method_set_arguments(call, argument);

  return call;
error:
  return NULL;
}
