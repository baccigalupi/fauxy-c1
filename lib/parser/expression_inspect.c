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

  Array *exp_pairs = NULL;
  Array *class_bit_pairs = NULL;

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

  class_bit_pairs = Array_create(2);
  verify(class_bit_pairs);
  array_push(class_bit_pairs, class_pair);
  array_push(class_bit_pairs, bit_pair);

  exp_value = json_gen_wrap_pairs(class_bit_pairs);
  verify(exp_value);

  exp_pair = json_gen_bald_pair(exp_key, exp_value);
  verify(exp_pair);

  exp_pairs = Array_create(1);
  verify(exp_pairs);
  array_push(exp_pairs, exp_pair);

  String *json = json_gen_wrap_pairs(exp_pairs);
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

  array_free(class_bit_pairs);
  array_free(exp_pairs);

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

  Array *type_bit_pairs = NULL;
  Array *exp_pairs = NULL;

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

  type_bit_pairs = Array_create(2);
  verify(type_bit_pairs);
  array_push(type_bit_pairs, type_pair);
  array_push(type_bit_pairs, bit_pair);

  exp_value = json_gen_wrap_pairs(type_bit_pairs);
  verify(exp_value);
  exp_pair = json_gen_bald_pair(exp_key, exp_value);
  verify(exp_pair);

  exp_pairs = Array_create(1);
  verify(exp_pairs);
  array_push(exp_pairs, exp_pair);

  String *json = json_gen_wrap_pairs(exp_pairs);
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

  array_free(type_bit_pairs);
  array_free(exp_pairs);

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

String *fxp_collection_inspect(FxP_Expression *expression) {
  String *exp_key = NULL;
  String *exp_value = NULL;
  String *exp_pair = NULL;
  Array *exp_array = NULL;
  Array *element_inspections = NULL;

  exp_key = fxp_expression_type_description(expression);
  verify(exp_key);

  element_inspections = array_map(fxp_expression_value(expression), fxp_inspect);
  verify(element_inspections);

  exp_value = json_gen_wrap_array_pairs(element_inspections);
  verify(exp_value);

  exp_pair = json_gen_bald_pair(exp_key, exp_value);
  verify(exp_pair);

  exp_array = Array_create(1);
  verify(exp_array);
  array_push(exp_array, exp_pair);

  String *json = json_gen_wrap_pairs(exp_array);

  string_free(exp_key);
  string_free(exp_value);
  array_free(element_inspections);
  array_free(exp_array);

  return json;
error:
  if (exp_key) { string_free(exp_key); }
  if (exp_value) { string_free(exp_value); }
  if (exp_pair) { string_free(exp_pair); }
  if (element_inspections) { string_free(element_inspections); }
  if (exp_array) { string_free(exp_array); }

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
    description = String_create("UNKNOWN STATEMENT");
  }

  verify(description);
  return description;
error:
  return NULL;
}

// map iterator for return array of inspections
// also can be used for regular inspection
void *fxp_inspect(void *element) {
  FxP_Expression *expression = (FxP_Expression *)element;

  String *json;
  int type = fxp_expression_type(expression);

  if (type == FXP_ST_LITERAL) {
    json = fxp_literal_inspect(expression);
  } else if (type == FXP_ST_LOOKUP) {
    json = fxp_lookup_inspect(expression);
  } else if (type == FXP_ST_METHOD) {
    json = String_create("method_call");
  } else if (type == FXP_ST_FUNCTION) {
    json = String_create("function_definition");
  } else if (type == FXP_ST_GROUPED) {
    json = fxp_collection_inspect(expression);
  } else if (type == FXP_ST_LIST) {
    json = fxp_collection_inspect(expression);
  } else if (type == FXP_ST_METHOD_ARGUMENTS) {
    json = fxp_collection_inspect(expression);
  } else if (type == FXP_ST_FUNCTION_ARGUMENTS) {
    json = fxp_collection_inspect(expression);
  } else if (type == FXP_ST_LOCAL_ASSIGN) {
    json = String_create("local_assignment");
  } else if (type == FXP_ST_COLON_EXPRESSION) {
    json = String_create("colon_expression");
  } else if (type == FXP_ST_EXPRESSIONS) {
    json = fxp_collection_inspect(expression);
  } else {
    json = String_create("UNKNOWN STATEMENT");
  }

  verify(json);
  return json;
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
