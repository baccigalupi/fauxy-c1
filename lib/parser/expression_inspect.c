#include "../bricks/string.h"
#include "../bricks/json_gen.h"
#include "expression_inspect.h"

String *fxp_literal_inspect(FxP_Literal *expression) {
  String *exp_key = NULL;
  String *exp_value = NULL;
  String *exp_pair = NULL;

  String *class_key = NULL;
  String *class_value = NULL;
  String *class_pair = NULL;

  String *bit_key = NULL;
  String *bit_value = NULL;
  String *bit_pair = NULL;

  exp_key = fxp_expression_type_description(expression);
  verify(exp_key);

  class_key = String_create("class");
  verify(class_key);
  class_value = fxp_literal_class_description(expression);
  verify(class_value);
  class_pair = json_gen_bald_pair(class_key, class_value);
  verify(class_pair);

  bit_key = String_create("bit");
  verify(bit_key);
  bit_value = fxp_bit_inspect(fxp_literal_bit(expression));
  verify(bit_value);
  bit_pair = json_gen_bald_pair(bit_key, bit_value);
  verify(bit_pair);

  exp_value = json_gen_wrap_pairs(2, class_pair, bit_pair);
  verify(exp_value);
  exp_pair = json_gen_bald_pair(exp_key, exp_value);
  verify(exp_pair);

  String *json = json_gen_wrap_pairs(1, exp_pair);
  verify(json);

  string_free(exp_key);
  string_free(exp_value);
  string_free(exp_pair);
  string_free(class_key);
  string_free(class_value);
  string_free(class_pair);
  string_free(bit_key);
  string_free(bit_value);
  string_free(bit_pair);

  return json;
error:
  if (exp_key) { string_free(exp_key); }
  if (exp_value) { string_free(exp_value); }
  if (exp_pair) { string_free(exp_pair); }
  if (class_key) { string_free(class_key); }
  if (class_value) { string_free(class_value); }
  if (class_pair) { string_free(class_pair); }
  if (bit_key) { string_free(bit_key); }
  if (bit_value) { string_free(bit_value); }
  if (bit_pair) { string_free(bit_pair); }

  return NULL;
}

String *fxp_lookup_inspect(FxP_Lookup *expression) {
  // "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}}"
  String *exp_key = NULL;
  String *exp_value = NULL;
  String *exp_pair = NULL;

  String *type_key = NULL;
  String *type_value = NULL;
  String *type_pair = NULL;

  String *bit_key = NULL;
  String *bit_value = NULL;
  String *bit_pair = NULL;

  exp_key = fxp_expression_type_description(expression);
  verify(exp_key);

  type_key = String_create("type");
  verify(type_key);
  type_value = fxp_lookup_type_description(expression);
  verify(type_value);
  type_pair = json_gen_bald_pair(type_key, type_value);
  verify(type_pair);

  bit_key = String_create("bit");
  verify(bit_key);
  bit_value = fxp_bit_inspect(fxp_literal_bit(expression));
  verify(bit_value);
  bit_pair = json_gen_bald_pair(bit_key, bit_value);
  verify(bit_pair);

  exp_value = json_gen_wrap_pairs(2, type_pair, bit_pair);
  verify(exp_value);
  exp_pair = json_gen_bald_pair(exp_key, exp_value);
  verify(exp_pair);

  String *json = json_gen_wrap_pairs(1, exp_pair);
  verify(json);

  string_free(exp_key);
  string_free(exp_value);
  string_free(exp_pair);
  string_free(type_key);
  string_free(type_value);
  string_free(type_pair);
  string_free(bit_key);
  string_free(bit_value);
  string_free(bit_pair);

  return json;
error:
  if (exp_key) { string_free(exp_key); }
  if (exp_value) { string_free(exp_value); }
  if (exp_pair) { string_free(exp_pair); }
  if (type_key) { string_free(type_key); }
  if (type_value) { string_free(type_value); }
  if (type_pair) { string_free(type_pair); }
  if (bit_key) { string_free(bit_key); }
  if (bit_value) { string_free(bit_value); }
  if (bit_pair) { string_free(bit_pair); }

  return NULL;
}


String *fxp_expression_type_description(FxP_Expression *expression) {
  String *description;
  int type = fxp_expression_type(expression);

  if (type == FXP_ST_LITERAL) {
    description = String_create("literal");
  } else if (type == FXP_ST_LOOKUP) {
    description = String_create("lookup");
  } else if (type == FXP_ST_METHOD) {
    description = String_create("method_call");
  } else if (type == FXP_ST_FUNCTION) {
    description = String_create("function_definition");
  } else if (type == FXP_ST_GROUPED) {
    description = String_create("grouped_expression");
  } else if (type == FXP_ST_LIST) {
    description = String_create("list");
  } else if (type == FXP_ST_METHOD_ARGUMENTS) {
    description = String_create("method_arguments");
  } else if (type == FXP_ST_FUNCTION_ARGUMENTS) {
    description = String_create("function_arguments");
  } else if (type == FXP_ST_LOCAL_ASSIGN) {
    description = String_create("local_assignment");
  } else if (type == FXP_ST_COLON_EXPRESSION) {
    description = String_create("colon_expression");
  } else if (type == FXP_ST_EXPRESSIONS) {
    description = String_create("expression");
  } else {
    description = String_create("UNKNOWS STATEMENT");
  }

  verify(description);
  return description;
error:
  return NULL;
}

String *fxp_literal_class_description(FxP_Literal *literal) {
  String *description;

  if (fxp_literal_type(literal) == TOKEN_STRING) {
    description = String_create("\"String\"");
  } else if (fxp_literal_type(literal) == TOKEN_EVAL_STRING) {
    description = String_create("\"String.Evaluable\"");
  } else if (fxp_literal_type(literal) == TOKEN_REGEX) {
    description = String_create("\"Regex\"");
  } else if (fxp_literal_type(literal) == TOKEN_SYMBOL) {
    description = String_create("\"Symbol\"");
  } else if (fxp_literal_type(literal) == TOKEN_INTEGER) {
    description = String_create("\"Integer\"");
  } else if (fxp_literal_type(literal) == TOKEN_FLOAT) {
    description = String_create("\"Float\"");
  } else if (fxp_literal_type(literal) == TOKEN_NIL) {
    description = String_create("\"Nil\"");
  } else if (fxp_literal_type(literal) == TOKEN_TRUE) {
    description = String_create("\"True\"");
  } else if (fxp_literal_type(literal) == TOKEN_FALSE) {
    description = String_create("\"False\"");
  } else {
    description = String_create_blank();
  }

  verify(description);

  return description;
error:
  return NULL;
}

String *fxp_lookup_type_description(FxP_Lookup *lookup) {
  String *description;

  if (fxp_lookup_type(lookup) == TOKEN_ID) {
    description = String_create("\"Identifier\"");
  } else {
    description = String_create("\"Class Identifier\"");
  }

  verify(description);

  return description;
error:
  return NULL;
}
