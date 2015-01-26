#include "../bricks/string.h"
#include "../bricks/json_gen.h"
#include "expression_inspect.h"

// map iterator for return array of inspections
// also can be used for regular inspection
void *fxp_inspect(void *element) {
  if (!element) { return FxB_String_create("\"NULL STATEMENT\""); }

  FxP_Expression *expression = (FxP_Expression *)element;
  FxB_String *unwrapped_pair = NULL;
  FxB_Array *pair_array = NULL;

  FxB_String *json;
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
    unwrapped_pair = fxp_list_body_inspect(expression);
  } else if (type == FXP_ST_METHOD_ARGUMENTS) {
    unwrapped_pair = fxp_list_body_inspect(expression);
  } else if (type == FXP_ST_FUNCTION_ARGUMENTS) {
    unwrapped_pair = fxp_list_body_inspect(expression);
  } else if (type == FXP_ST_LOCAL_ASSIGN) {
    unwrapped_pair = fxp_left_right_inspect(expression);
  } else if (type == FXP_ST_COLON_EXPRESSION) {
    unwrapped_pair = fxp_left_right_inspect(expression);
  } else if (type == FXP_ST_EXPRESSIONS) {
    unwrapped_pair = fxp_collection_body_inspect(expression);
  } else {
    unwrapped_pair = FxB_String_create("\"UNKNOWN STATEMENT\"");
    printf("printing unknown statement: %d\n", type);
  }

  verify(unwrapped_pair);
  pair_array = FxB_Array_create(1);
  verify(pair_array);
  fxb_array_push(pair_array, unwrapped_pair);

  json = fxb_json_gen_wrap_pairs(pair_array);
  verify(json);

  fxb_string_free(unwrapped_pair);
  fxb_array_free(pair_array);

  return json;
error:
  if (unwrapped_pair) { fxb_string_free(unwrapped_pair); }
  if (pair_array) { fxb_array_free(pair_array); }
  return NULL;
}

FxB_String *fxp_expression_join(FxP_Expression *expression, FxB_String *value) {
  FxB_String *key = NULL;
  FxB_String *bald_pair = NULL;
  FxB_Array  *pairs = FxB_Array_create(1);
  verify(pairs);

  key =  fxp_expression_type_description(expression);
  bald_pair = fxb_json_gen_bald_pair(key, value);
  verify(bald_pair);

  fxb_array_push(pairs, bald_pair);

  FxB_String *json = fxb_json_gen_join_pairs(pairs, ", ");
  verify(json);

  fxb_string_free(key);
  fxb_string_free(bald_pair);
  fxb_array_free(pairs);

  return json;
error:
  if (key) { fxb_string_free(key); }
  if (bald_pair) { fxb_string_free(bald_pair); }
  if (pairs) { fxb_array_free(pairs); }

  return NULL;
}

FxB_String *fxp_literal_body_inspect(FxP_Literal *expression) {
  FxB_String *exp_value = NULL;

  FxB_String *class_key = NULL;
  FxB_String *class_value = NULL;
  FxB_String *class_pair = NULL;

  FxB_String *bit_key = NULL;
  FxB_String *bit_value = NULL;
  FxB_String *bit_pair = NULL;

  FxB_Array *class_bit_pairs = NULL;

  class_bit_pairs = FxB_Array_create(2);
  verify(class_bit_pairs);

  class_key = FxB_String_create("class");
  class_value = fxp_literal_class_description(expression);
  class_pair = fxb_json_gen_bald_pair(class_key, class_value);
  verify(class_pair);
  fxb_array_push(class_bit_pairs, class_pair);

  if (fxp_literal_bit(expression)) {
    bit_key = FxB_String_create("bit");
    bit_value = fxp_bit_inspect(fxp_literal_bit(expression));
    bit_pair = fxb_json_gen_bald_pair(bit_key, bit_value);
    verify(bit_pair);
    fxb_array_push(class_bit_pairs, bit_pair);
  } else if ( fxp_literal_type(expression) == TOKEN_TRUE || fxp_literal_type(expression) == TOKEN_FALSE ) {
    bit_key = FxB_String_create("value");
    if ( fxp_literal_type(expression) == TOKEN_TRUE ) {
      bit_value = FxB_String_create("true");
    } else {
      bit_value = FxB_String_create("false");
    }
    bit_pair = fxb_json_gen_bald_pair(bit_key, bit_value);
    verify(bit_pair);
    fxb_array_push(class_bit_pairs, bit_pair);
  }

  exp_value = fxb_json_gen_wrap_pairs(class_bit_pairs);
  FxB_String *json = fxp_expression_join(expression, exp_value);
  verify(json);

  fxb_string_free(exp_value);
  fxb_string_free(class_key);
  fxb_string_free(class_value);
  fxb_string_free(class_pair);
  if (bit_key)    { fxb_string_free(bit_key); }
  if (bit_value)  { fxb_string_free(bit_value); }
  if (bit_pair)   { fxb_string_free(bit_pair); }

  fxb_array_free(class_bit_pairs);

  return json;
error:
  if (exp_value) { fxb_string_free(exp_value); }
  if (class_key) { fxb_string_free(class_key); }
  if (class_value) { fxb_string_free(class_value); }
  if (class_pair) { fxb_string_free(class_pair); }
  if (bit_key) { fxb_string_free(bit_key); }
  if (bit_value) { fxb_string_free(bit_value); }
  if (bit_pair) { fxb_string_free(bit_pair); }

  if (class_bit_pairs) { fxb_array_free(class_bit_pairs); }

  return NULL;
}

FxB_String *fxp_lookup_body_inspect(FxP_Lookup *expression) {
  // "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}}"
  FxB_String *exp_value = NULL;

  FxB_String *type_key = NULL;
  FxB_String *type_value = NULL;
  FxB_String *type_pair = NULL;

  FxB_String *bit_key = NULL;
  FxB_String *bit_value = NULL;
  FxB_String *bit_pair = NULL;

  FxB_Array *type_bit_pairs = NULL;

  type_key = FxB_String_create("type");
  type_value = fxp_lookup_type_description(expression);
  type_pair = fxb_json_gen_bald_pair(type_key, type_value);
  verify(type_pair);

  bit_key = FxB_String_create("bit");
  bit_value = fxp_bit_inspect(fxp_literal_bit(expression));
  bit_pair = fxb_json_gen_bald_pair(bit_key, bit_value);
  verify(bit_pair);

  type_bit_pairs = FxB_Array_create(2);
  verify(type_bit_pairs);
  fxb_array_push(type_bit_pairs, type_pair);
  fxb_array_push(type_bit_pairs, bit_pair);

  exp_value = fxb_json_gen_wrap_pairs(type_bit_pairs);
  FxB_String *json = fxp_expression_join(expression, exp_value);
  verify(json);

  fxb_string_free(exp_value);
  fxb_string_free(type_key);
  fxb_string_free(type_value);
  fxb_string_free(type_pair);
  fxb_string_free(bit_key);
  fxb_string_free(bit_value);
  fxb_string_free(bit_pair);

  fxb_array_free(type_bit_pairs);

  return json;
error:
  if (exp_value) { fxb_string_free(exp_value); }
  if (type_key) { fxb_string_free(type_key); }
  if (type_value) { fxb_string_free(type_value); }
  if (type_pair) { fxb_string_free(type_pair); }
  if (bit_key) { fxb_string_free(bit_key); }
  if (bit_value) { fxb_string_free(bit_value); }
  if (bit_pair) { fxb_string_free(bit_pair); }

  if (type_bit_pairs) { fxb_array_free(type_bit_pairs); }

  return NULL;
}

// array iterator for freeing all the inspections
void fxp_free_inspection(void *str) {
  fxb_string_free(str);
}

FxB_String *fxp_collection_body_inspect(FxP_Expression *expression) {
  FxB_String *exp_value = NULL;
  FxB_Array  *element_inspections = NULL;

  element_inspections = fxb_array_map(fxp_expression_value(expression), fxp_inspect);
  verify(element_inspections);

  exp_value = fxb_json_gen_wrap_array_pairs(element_inspections);
  verify(exp_value);

  FxB_String *json = fxp_expression_join(expression, exp_value);

  fxb_string_free(exp_value);
  fxb_array_each(element_inspections, fxp_free_inspection);
  fxb_array_free(element_inspections);

  return json;
error:
  if (exp_value) { fxb_string_free(exp_value); }
  if (element_inspections) {
    fxb_array_each(element_inspections, fxp_free_inspection);
    fxb_string_free(element_inspections);
  }

  return NULL;
}

FxB_String *fxp_list_body_inspect(FxP_Expression *expression) {
  FxB_String *exp_value = NULL;
  FxB_Array  *element_inspections = NULL;

  element_inspections = fxb_array_reverse_map(fxp_expression_value(expression), fxp_inspect);
  verify(element_inspections);

  exp_value = fxb_json_gen_wrap_array_pairs(element_inspections);
  verify(exp_value);

  FxB_String *json = fxp_expression_join(expression, exp_value);

  fxb_string_free(exp_value);
  fxb_array_each(element_inspections, fxp_free_inspection);
  fxb_array_free(element_inspections);

  return json;
error:
  if (exp_value) { fxb_string_free(exp_value); }
  if (element_inspections) {
    fxb_array_each(element_inspections, fxp_free_inspection);
    fxb_string_free(element_inspections);
  }

  return NULL;
}

FxB_String *fxp_method_body_inspect(FxP_Expression *expression) {
  /*[receiver, method_name, method_arguments]*/
  FxB_String *receiver_key = NULL;
  FxB_String *receiver_value = NULL;
  FxB_String *receiver_pair = NULL;

  FxB_String *message_key = NULL;
  FxB_String *message_value = NULL;
  FxB_String *message_pair = NULL;

  FxB_String *arg_value = NULL;

  FxB_String *exp_value = NULL;

  FxB_Array  *exp_values = FxB_Array_create(3);
  verify(exp_values);

  if ( fxp_method_receiver(expression) ) {
    receiver_key = FxB_String_create("receiver");
    receiver_value = fxp_inspect(fxp_method_receiver(expression));
    receiver_pair = fxb_json_gen_bald_pair(receiver_key, receiver_value);
    verify(receiver_pair);
    fxb_array_push(exp_values, receiver_pair);
  }

  message_key = FxB_String_create("message");
  message_value = fxp_inspect(fxp_method_message(expression));
  message_pair = fxb_json_gen_bald_pair(message_key, message_value);
  verify(message_pair);
  fxb_array_push(exp_values, message_pair);

  if ( fxp_method_arguments(expression) ) {
    arg_value = fxp_list_body_inspect(fxp_method_arguments(expression));
    verify(arg_value);
    fxb_array_push(exp_values, arg_value);
  }

  exp_value = fxb_json_gen_wrap_pairs(exp_values);

  FxB_String *json = fxp_expression_join(expression, exp_value);
  verify(json);

  if (receiver_key) { fxb_string_free(receiver_key); }
  if (receiver_value) { fxb_string_free(receiver_value); }
  if (receiver_pair) { fxb_string_free(receiver_pair); }

  if (message_key) { fxb_string_free(message_key); }
  if (message_value) { fxb_string_free(message_value); }
  if (message_pair) { fxb_string_free(message_pair); }

  if (arg_value) { fxb_string_free(arg_value); }

  if (exp_value) { fxb_string_free(exp_value); }

  if (exp_values) { fxb_array_free(exp_values); }

  return json;
error:
  if (receiver_key) { fxb_string_free(receiver_key); }
  if (receiver_value) { fxb_string_free(receiver_value); }
  if (receiver_pair) { fxb_string_free(receiver_pair); }

  if (message_key) { fxb_string_free(message_key); }
  if (message_value) { fxb_string_free(message_value); }
  if (message_pair) { fxb_string_free(message_pair); }

  if (arg_value) { fxb_string_free(arg_value); }

  if (exp_value) { fxb_string_free(exp_value); }

  if (exp_values) { fxb_array_free(exp_values); }

  return NULL;
}

FxB_String *fxp_function_body_inspect(FxP_Expression *expression) {
  /*[arguments, expressions]*/
  FxB_String *arguments_value = NULL;

  FxB_String *expressions_key = NULL;
  FxB_String *expressions_value = NULL;
  FxB_String *expressions_pair = NULL;

  FxB_String *exp_value = NULL;

  FxB_Array *exp_values = FxB_Array_create(2);
  verify(exp_values);

  if ( fxp_function_arguments(expression) ) {
    arguments_value = fxp_list_body_inspect(fxp_function_arguments(expression));
    verify(arguments_value);
    fxb_array_push(exp_values, arguments_value);
  }

  expressions_value = fxp_collection_body_inspect(fxp_function_expressions(expression));
  verify(expressions_value);
  fxb_array_push(exp_values, expressions_value);

  exp_value = fxb_json_gen_wrap_pairs(exp_values);
  FxB_String *json = fxp_expression_join(expression, exp_value);
  verify(json);

  if (arguments_value) { fxb_string_free(arguments_value); }

  if (arguments_value) { fxb_string_free(arguments_value); }

  if (expressions_key) { fxb_string_free(expressions_key); }
  if (expressions_value) { fxb_string_free(expressions_value); }
  if (expressions_pair) { fxb_string_free(expressions_pair); }

  if (exp_value) { fxb_string_free(exp_value); }

  if (exp_values) { fxb_array_free(exp_values); }

  return json;
error:
  if (arguments_value) { fxb_string_free(arguments_value); }

  if (expressions_key) { fxb_string_free(expressions_key); }
  if (expressions_value) { fxb_string_free(expressions_value); }
  if (expressions_pair) { fxb_string_free(expressions_pair); }

  if (exp_value) { fxb_string_free(exp_value); }

  if (exp_values) { fxb_array_free(exp_values); }

  return NULL;
}

FxB_String *fxp_left_right_inspect(FxP_Expression *expression) {
  // Local assignment: [local, value]
  FxB_String *left_key = NULL;
  FxB_String *left_value = NULL;
  FxB_String *left_pair = NULL;

  FxB_String *right_key = NULL;
  FxB_String *right_value = NULL;
  FxB_String *right_pair = NULL;

  FxB_String *exp_value = NULL;
  FxB_Array *exp_values = FxB_Array_create(2);
  verify(exp_values);

  left_key = FxB_String_create("left");
  left_value = fxp_inspect(fxp_expression_left(expression));
  left_pair = fxb_json_gen_bald_pair(left_key, left_value);
  verify(left_pair);
  fxb_array_push(exp_values, left_pair);

  right_key = FxB_String_create("right");
  right_value = fxp_inspect(fxp_expression_right(expression));
  right_pair = fxb_json_gen_bald_pair(right_key, right_value);
  verify(right_pair);
  fxb_array_push(exp_values, right_pair);

  exp_value = fxb_json_gen_wrap_pairs(exp_values);
  FxB_String *json = fxp_expression_join(expression, exp_value);

  fxb_string_free(right_key);
  fxb_string_free(right_value);
  fxb_string_free(right_pair);
  fxb_string_free(left_key);
  fxb_string_free(left_value);
  fxb_string_free(left_pair);
  fxb_string_free(exp_value);
  fxb_array_free(exp_values);

  return json;
error:
  if (right_key)    {fxb_string_free(right_key); }
  if (right_key)    {fxb_string_free(right_value); }
  if (right_key)    {fxb_string_free(right_pair); }
  if (left_key)     {fxb_string_free(left_key); }
  if (left_value)   {fxb_string_free(left_value); }
  if (left_pair)    {fxb_string_free(left_pair); }
  if (exp_value)    {fxb_string_free(exp_value); }

  if(exp_values) { fxb_array_free(exp_values); }

  return NULL;
}

FxB_String *fxp_expression_type_description(FxP_Expression *expression) {
  FxB_String *description;
  int type = fxp_expression_type(expression);

  if (type == FXP_ST_LITERAL) {
    description = FxB_String_create("literal");
  } else if (type == FXP_ST_LOOKUP) {
    description = FxB_String_create("lookup");
  } else if (type == FXP_ST_METHOD) {
    description = FxB_String_create("method_call");
  } else if (type == FXP_ST_FUNCTION) {
    description = FxB_String_create("function_definition");
  } else if (type == FXP_ST_GROUPED) {
    description = FxB_String_create("grouped_expression");
  } else if (type == FXP_ST_LIST) {
    description = FxB_String_create("list");
  } else if (type == FXP_ST_METHOD_ARGUMENTS) {
    description = FxB_String_create("method_arguments");
  } else if (type == FXP_ST_FUNCTION_ARGUMENTS) {
    description = FxB_String_create("function_arguments");
  } else if (type == FXP_ST_LOCAL_ASSIGN) {
    description = FxB_String_create("local_assignment");
  } else if (type == FXP_ST_COLON_EXPRESSION) {
    description = FxB_String_create("colon_expression");
  } else if (type == FXP_ST_EXPRESSIONS) {
    description = FxB_String_create("expressions");
  } else {
    description = FxB_String_create("\"UNKNOWN STATEMENT\"");
    printf("unknown statement type: %d\n", type);
  }

  verify(description);
  return description;
error:
  return NULL;
}

FxB_String *fxp_literal_class_description(FxP_Literal *literal) {
  FxB_String *description;

  if (fxp_literal_type(literal) == TOKEN_STRING) {
    description = FxB_String_create("\"String\"");
  } else if (fxp_literal_type(literal) == TOKEN_EVAL_STRING) {
    description = FxB_String_create("\"EvalString\"");
  } else if (fxp_literal_type(literal) == TOKEN_REGEX) {
    description = FxB_String_create("\"Regex\"");
  } else if (fxp_literal_type(literal) == TOKEN_SYMBOL) {
    description = FxB_String_create("\"Symbol\"");
  } else if (fxp_literal_type(literal) == TOKEN_INTEGER) {
    description = FxB_String_create("\"Integer\"");
  } else if (fxp_literal_type(literal) == TOKEN_FLOAT) {
    description = FxB_String_create("\"Float\"");
  } else if (fxp_literal_type(literal) == TOKEN_NIL) {
    description = FxB_String_create("\"Nil\"");
  } else if (fxp_literal_type(literal) == TOKEN_TRUE) {
    description = FxB_String_create("\"Boolean\"");
  } else if (fxp_literal_type(literal) == TOKEN_FALSE) {
    description = FxB_String_create("\"Boolean\"");
  } else {
    description = FxB_String_create_blank();
  }

  verify(description);

  return description;
error:
  return NULL;
}

FxB_String *fxp_lookup_type_description(FxP_Lookup *lookup) {
  FxB_String *description;

  if (fxp_lookup_type(lookup) == TOKEN_ID) {
    description = FxB_String_create("\"Identifier\"");
  } else {
    description = FxB_String_create("\"Class Identifier\"");
  }

  verify(description);

  return description;
error:
  return NULL;
}
