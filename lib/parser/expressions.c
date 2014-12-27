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
  fx_expression_type(argument) = FX_ST_ARG_LIST;
  fx_method_set_arguments(call, argument);

  return call;
error:
  return NULL;
}

FxMethodCall *fx_method_call_convert_implicit(FxMethodCall *self, FxExpression *receiver) {
  fx_method_set_receiver(self, receiver);
  return self;
}

FxMethodCall *fx_method_call_add_function_argument(FxMethodCall *method, FxFunction *function) {
  FxArgumentList *list;

  if (fx_expression_length(method) == 2) {
    list = FxExpression_create(FX_ST_ARG_LIST);
    verify(list);
    fx_method_set_arguments(method, list);
  }

  list = fx_method_arguments(method);
  fx_list_unshift(list, function);

  return method;
error:
  return NULL;
}

FxMethodCall *FxMethodCall_create_no_args(FxExpression *receiver, FxBit *message) {
  FxMethodCall *method = FxMethodCall_create();
  verify_memory(method);

  fx_method_set_receiver(method, receiver);
  fx_method_set_message(method, message);

  return method;
error:
  return NULL;
}

FxMethodCall *FxMethodCall_create_operator(FxExpression *receiver, FxBit *message, FxExpression *argument) {
  FxArgumentList *list = fx_argument_list_convert(argument);
  verify(list);

  FxMethodCall *method = FxMethodCall_create();
  verify(method);

  fx_method_set_receiver(method, receiver);
  fx_method_set_message(method, message);
  fx_method_set_arguments(method, list);

  return method;
error:
  if (list) { fx_expression_free(list); }
  return NULL;
}

FxGroupedExpression *FxGroupedExpression_create(FxExpression *value) {
  FxGroupedExpression *group = FxExpression_create(FX_ST_GROUPED);
  verify_memory(group);

  if (value) {
    fx_expression_push(group, value);
  }
  return group;
error:
  return NULL;
}

FxList *fx_list_convert(FxGroupedExpression *group) {
  fx_expression_type(group) = FX_ST_LIST;
  return group;
}

FxList *FxList_create_deferred() {
  FxLiteral *value = FxLiteral_create(NULL, TOKEN_DEFERRED_ARGUMENT);
  verify(value);

  FxList *list = FxExpression_create(FX_ST_LIST);
  verify(list);
  fx_expression_push(list, value);

  return list;
error:
  if (value) { fx_literal_free(value); }
  return NULL;
}

FxList *FxList_create_double(FxExpression *first, FxExpression *second) {
  FxList *list = FxExpression_create(FX_ST_LIST);
  verify(list);

  fx_expression_push(list, first);
  fx_expression_push(list, second);

  return list;
error:
  return NULL;
}

// this is pretty inefficient for longer lists since tail is finished first
// would be better to just reverse the index on read and write to end
FxList *fx_list_unshift(FxList *list, FxExpression *value) {
  int length = fx_list_length(list);

  // shove last element in again to trigger auto expansion if necessary
  fx_expression_push(list, fx_list_get(list, length - 1));

  // move each element to the one behind it
  int i;
  for (i = 1; i <= length; i++) {
    fx_list_set(list, i, fx_list_get(list, i - 1));
  }

  // put new value in the front
  fx_list_set(list, 0, value);

  return list;
}

FxArgumentList *fx_argument_list_convert(FxExpression *expression) {
  FxArgumentList *list = NULL;
  int type = fx_expression_type(expression);

  if (type == FX_ST_LIST || type == FX_ST_GROUPED) {
    list = expression;
  } else {
    list = FxGroupedExpression_create(expression);
    verify(list);
  }

  fx_expression_type(list) = FX_ST_ARG_LIST;
  return list;
error:
  return NULL;
}
