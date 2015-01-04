#include "../bricks/string.h"
#include "../bricks/json_gen.h"
#include "expression_inspect.h"

// map iterator for return array of inspections
// also can be used for regular inspection
void *fxp_inspect(void *element) {
  FxP_Expression *expression = (FxP_Expression *)element;
  String *unwrapped_pair = NULL;
  Array *pair_array = NULL;

  String *json;
  int type = fxp_expression_type(expression);

  if (type == FXP_ST_LITERAL) {
    unwrapped_pair = fxp_literal_body_inspect(expression);
  } else if (type == FXP_ST_LOOKUP) {
    unwrapped_pair = fxp_lookup_body_inspect(expression);
  } else if (type == FXP_ST_METHOD) {
    unwrapped_pair = fxp_method_body_inspect(expression);
  } else if (type == FXP_ST_FUNCTION) {
    unwrapped_pair = fxp_function_body_inspect(expression);
  } else if (type == FXP_ST_GROUPED) {
    unwrapped_pair = fxp_collection_body_inspect(expression);
  } else if (type == FXP_ST_LIST) {
    unwrapped_pair = fxp_collection_body_inspect(expression);
  } else if (type == FXP_ST_METHOD_ARGUMENTS) {
    unwrapped_pair = fxp_collection_body_inspect(expression);
  } else if (type == FXP_ST_FUNCTION_ARGUMENTS) {
    unwrapped_pair = fxp_collection_body_inspect(expression);
  } else if (type == FXP_ST_LOCAL_ASSIGN) {
    unwrapped_pair = fxp_local_assign_body_inspect(expression);
  } else if (type == FXP_ST_COLON_EXPRESSION) {
    unwrapped_pair = String_create("colon_expression");
  } else if (type == FXP_ST_EXPRESSIONS) {
    unwrapped_pair = fxp_collection_body_inspect(expression);
  } else {
    unwrapped_pair = String_create("\"UNKNOWN STATEMENT\"");
    printf("printing unknown statement: %d\n", type);
  }

  verify(unwrapped_pair);
  pair_array = Array_create(1);
  verify(pair_array);
  array_push(pair_array, unwrapped_pair);

  json = json_gen_wrap_pairs(pair_array);
  verify(json);

  string_free(unwrapped_pair);
  array_free(pair_array);

  return json;
error:
  if (unwrapped_pair) { string_free(unwrapped_pair); }
  if (pair_array) { array_free(pair_array); }
  return NULL;
}

String *fxp_literal_body_inspect(FxP_Literal *expression) {
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

  String *json = json_gen_join_pairs(exp_pairs, ", ");
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

String *fxp_lookup_body_inspect(FxP_Lookup *expression) {
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

  String *json = json_gen_join_pairs(exp_pairs, ", ");
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

String *fxp_collection_body_inspect(FxP_Expression *expression) {
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

  String *json = json_gen_join_pairs(exp_array, ", ");

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

String *fxp_method_body_inspect(FxP_Expression *expression) {
  /*[receiver, method_name, method_arguments]*/
  String *receiver_key = NULL;
  String *receiver_value = NULL;
  String *receiver_pair = NULL;

  String *message_key = NULL;
  String *message_value = NULL;
  String *message_pair = NULL;

  String *arg_value = NULL;

  String *exp_key = NULL;
  String *exp_value = NULL;
  String *exp_pair = NULL;

  Array *json_pair = NULL;

  Array  *exp_values = Array_create(3);
  verify(exp_values);

  if ( fxp_method_receiver(expression) ) {
    receiver_key = String_create("receiver");
    verify(receiver_key);
    receiver_value = fxp_inspect(fxp_method_receiver(expression));
    verify(receiver_value);
    receiver_pair = json_gen_bald_pair(receiver_key, receiver_value);
    verify(receiver_pair);
    array_push(exp_values, receiver_pair);
  }

  message_key = String_create("message");
  verify(message_key);
  message_value = fxp_inspect(fxp_method_message(expression));
  verify(message_value);
  message_pair = json_gen_bald_pair(message_key, message_value);
  verify(message_pair);
  array_push(exp_values, message_pair);

  if ( fxp_method_arguments(expression) ) {
    arg_value = fxp_collection_body_inspect(fxp_method_arguments(expression));
    verify(arg_value);
    array_push(exp_values, arg_value);
  }

  exp_key = fxp_expression_type_description(expression);
  verify(exp_key);
  exp_value = json_gen_wrap_pairs(exp_values);
  verify(exp_value);
  exp_pair = json_gen_bald_pair(exp_key, exp_value);

  json_pair = Array_create(1);
  verify(json_pair);
  array_push(json_pair, exp_pair);

  String *json = json_gen_join_pairs(json_pair, ", ");
  verify(json);

  if (receiver_key) { string_free(receiver_key); }
  if (receiver_value) { string_free(receiver_value); }
  if (receiver_pair) { string_free(receiver_pair); }

  if (message_key) { string_free(message_key); }
  if (message_value) { string_free(message_value); }
  if (message_pair) { string_free(message_pair); }

  if (arg_value) { string_free(arg_value); }

  if (exp_key) { string_free(exp_key); }
  if (exp_value) { string_free(exp_value); }
  if (exp_pair) { string_free(exp_pair); }

  if (exp_values) { array_free(exp_values); }
  if (json_pair) { array_free(json_pair); }

  return json;
error:
  if (receiver_key) { string_free(receiver_key); }
  if (receiver_value) { string_free(receiver_value); }
  if (receiver_pair) { string_free(receiver_pair); }

  if (message_key) { string_free(message_key); }
  if (message_value) { string_free(message_value); }
  if (message_pair) { string_free(message_pair); }

  if (arg_value) { string_free(arg_value); }

  if (exp_key) { string_free(exp_key); }
  if (exp_value) { string_free(exp_value); }
  if (exp_pair) { string_free(exp_pair); }

  if (exp_values) { array_free(exp_values); }
  if (json_pair) { array_free(json_pair); }

  return NULL;
}

String *fxp_function_body_inspect(FxP_Expression *expression) {
  /*[arguments, expressions]*/
  String *arguments_value = NULL;

  String *expressions_key = NULL;
  String *expressions_value = NULL;
  String *expressions_pair = NULL;

  String *exp_key = NULL;
  String *exp_pair = NULL;
  String *exp_value = NULL;

  Array *exp_pairs = NULL;

  Array *exp_values = Array_create(2);
  verify(exp_values);

  if ( fxp_function_arguments(expression) ) {
    arguments_value = fxp_collection_body_inspect(fxp_function_arguments(expression));
    verify(arguments_value);
    array_push(exp_values, arguments_value);
  }

  expressions_value = fxp_collection_body_inspect(fxp_function_expressions(expression));
  verify(expressions_value);
  array_push(exp_values, expressions_value);

  exp_key = fxp_expression_type_description(expression);
  verify(exp_key);
  exp_value = json_gen_wrap_pairs(exp_values);
  verify(exp_value);
  exp_pair = json_gen_bald_pair(exp_key, exp_value);
  verify(exp_pair);

  exp_pairs = Array_create(1);
  array_push(exp_pairs, exp_pair);

  String *json = json_gen_join_pairs(exp_pairs, ", ");
  verify(json);

  if (arguments_value) { string_free(arguments_value); }

  if (arguments_value) { string_free(arguments_value); }

  if (expressions_key) { string_free(expressions_key); }
  if (expressions_value) { string_free(expressions_value); }
  if (expressions_pair) { string_free(expressions_pair); }

  if (exp_key) { string_free(exp_key); }
  if (exp_pair) { string_free(exp_pair); }
  if (exp_value) { string_free(exp_value); }

  if (exp_pairs) { array_free(exp_pairs); }
  if (exp_values) { array_free(exp_values); }

  return json;
error:
  if (arguments_value) { string_free(arguments_value); }

  if (expressions_key) { string_free(expressions_key); }
  if (expressions_value) { string_free(expressions_value); }
  if (expressions_pair) { string_free(expressions_pair); }

  if (exp_key) { string_free(exp_key); }
  if (exp_pair) { string_free(exp_pair); }
  if (exp_value) { string_free(exp_value); }

  if (exp_pairs) { array_free(exp_pairs); }
  if (exp_values) { array_free(exp_values); }

  return NULL;
}

String *fxp_local_assign_body_inspect(FxP_Expression *expression) {
  // Local assignment: [local, value]
  String *local_key = NULL;
  String *local_value = NULL;
  String *local_pair = NULL;

  String *value_key = NULL;
  String *value_value = NULL;
  String *value_pair = NULL;

  String *exp_key = NULL;
  String *exp_value = NULL;
  Array *exp_values = Array_create(2);
  verify(exp_values);

  local_key = String_create("local");
  verify(local_key);
  local_value = fxp_inspect(fxp_local_assignment_variable(expression));
  verify(local_value);
  local_pair = json_gen_bald_pair(local_key, local_value);
  verify(local_pair);
  array_push(exp_values, local_pair);

  value_key = String_create("value");
  verify(local_key);
  value_value = fxp_inspect(fxp_local_assignment_value(expression));
  verify(value_value);
  value_pair = json_gen_bald_pair(value_key, value_value);
  verify(value_pair);
  array_push(exp_values, value_pair);

  exp_key = fxp_expression_type_description(expression);
  verify(exp_key);
  exp_value = json_gen_wrap_pairs(exp_values);
  verify(exp_value);
  String *json = json_gen_bald_pair(exp_key, exp_value);

  string_free(value_key);
  string_free(value_value);
  string_free(value_pair);
  string_free(local_key);
  string_free(local_value);
  string_free(local_pair);
  string_free(exp_key);
  string_free(exp_value);
  array_free(exp_values);

  return json;
error:
  if (value_key)    {string_free(value_key); }
  if (value_key)    {string_free(value_value); }
  if (value_key)    {string_free(value_pair); }
  if (local_key)    {string_free(local_key); }
  if (local_value)  {string_free(local_value); }
  if (local_pair)   {string_free(local_pair); }
  if (exp_key)      {string_free(exp_key); }
  if (exp_value)    {string_free(exp_value); }

  if(exp_values) { array_free(exp_values); }

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
    description = String_create("expressions");
  } else {
    description = String_create("\"UNKNOWN STATEMENT\"");
    printf("unknown statement type: %d\n", type);
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
