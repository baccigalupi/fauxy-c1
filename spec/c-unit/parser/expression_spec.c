#include <string.h>

#include "../../../lib/parser/bit.h"
#include "../../../lib/parser/expressions.h"
#include "../../../lib/parser/expression_inspect.h"
#include "../lib/spec.h"

char *test_create_literal() {
  spec_describe("creating literal expression from bit");

  FxP_Bit *bit = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);

  assert_ints_equal(fxp_literal_type(literal), TOKEN_STRING, "type");
  assert_equal(fxp_literal_bit(literal), bit, "bit value");

  fxp_expression_free(literal);

  return NULL;
}

char *test_inspect_literal() {
  spec_describe("inspecting a literal expression");

  FxP_Bit *bit = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);

  String *inspection = fxp_inspect(literal);
  assert_strings_equal(string_value(inspection), "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}", "json");

  fxp_expression_free(literal);
  string_free(inspection);

  return NULL;
}

char *test_inspect_lookup() {
  spec_describe("inspecting a lookup expression");

  FxP_Bit *bit = FxP_Bit_create(TOKEN_ID, "foo");
  FxP_Literal *lookup = FxP_Lookup_create(bit, TOKEN_ID);

  String *inspection = fxp_inspect(lookup);
  assert_strings_equal(string_value(inspection), "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}}", "json");

  fxp_expression_free(lookup);
  string_free(inspection);

  return NULL;
}

char *test_inspect_list() {
  spec_describe("inspecting a list expression");

  FxP_Bit     *bit_1 = FxP_Bit_create(TOKEN_ID, "foo");
  FxP_Literal *arg_1 = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *arg_2 = FxP_Literal_create(bit_2, TOKEN_STRING);

  FxP_List    *list = FxP_List_create_double(arg_1, arg_2);

  String *inspection = fxp_inspect(list);
  char *expected = "{\"list\": [\n{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}},\n{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}\n]}";
  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_expression_free(list);
  string_free(inspection);

  return NULL;
}

char *test_inspect_implicit_method() {
  spec_describe("inspecting an implicit method call");

  FxP_Bit *bit_1 = FxP_Bit_create(TOKEN_ID, "print");
  FxP_Literal *message = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit *bit_2 = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *arg = FxP_Literal_create(bit_2, TOKEN_STRING);

  // print "hello world"
  FxP_Method *method = FxP_Method_create_implicit(message, arg);
  String *inspection = fxp_inspect(method);
  char *expected = "{\"method_call\": {\"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}, \"method_arguments\": [\n{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}\n]}}";
  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_expression_free(method);
  string_free(inspection);

  return NULL;
}

char *test_inspect_method_no_args() {
  spec_describe("inspecting a method call with no args");

  FxP_Bit *bit_1 = FxP_Bit_create(TOKEN_ID, "printer");
  FxP_Literal *receiver = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit *bit_2 = FxP_Bit_create(TOKEN_ID, "print");
  FxP_Literal *message = FxP_Lookup_create(bit_2, TOKEN_ID);

  // printer.print
  FxP_Method *method = FxP_Method_create_no_args(receiver, message);

  String *inspection = fxp_inspect(method);
  char *expected = "{\"method_call\": {\"receiver\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"printer\"}}}, \"message\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"print\"}}}}}";
  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_expression_free(method);
  string_free(inspection);

  return NULL;
}

char *test_inspect_function() {
  spec_describe("inspecting a function with arguments");

  // arguments
  FxP_Bit     *bit_1 = FxP_Bit_create(TOKEN_ID, "foo");
  FxP_Literal *arg_1 = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_create(TOKEN_ID, "bar");
  FxP_Literal *arg_2 = FxP_Lookup_create(bit_2, TOKEN_ID);

  FxP_List    *arguments = FxP_List_create_double(arg_1, arg_2);
  fxp_expression_type(arguments) = FXP_ST_FUNCTION_ARGUMENTS;

  // expressions
  FxP_Expressions *expressions = FxP_Expressions_create();

  // function
  FxP_Function *function = FxP_Function_create(arguments);
  fxp_function_set_expressions(function, expressions);

  String *inspection = fxp_inspect(function);
  char *expected = "{\"function_definition\": {"
                      "\"function_arguments\": [\n{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}},\n{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"bar\"}}}\n], "
                      "\"expressions\": [\n\n]"
                    "}}";
  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_expression_free(function);
  string_free(inspection);

  return NULL;
}

char *test_inspect_local_assignment() {
  spec_describe("inspecting local assignment expression");

  // arguments
  FxP_Bit     *bit_1 = FxP_Bit_create(TOKEN_ID, "greeting");
  FxP_Literal *local = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *value = FxP_Literal_create(bit_2, TOKEN_STRING);

  FxP_Expression *local_assignment = FxP_LocalAssign_create(local, value);
  String *inspection = fxp_inspect(local_assignment);

  char *expected = "{\"local_assignment\": {"
                      "\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"greeting\"}}}, "
                      "\"right\": {\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}"
                   "}}";

  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_expression_free(local_assignment);
  string_free(inspection);

  return NULL;
}

char *test_inspect_colon_expression() {
  spec_describe("inspecting colon expression");

  // arguments
  FxP_Bit     *bit_1 = FxP_Bit_create(TOKEN_ID, "greeting");
  FxP_Literal *attr = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *value = FxP_Literal_create(bit_2, TOKEN_STRING);

  FxP_Expression *attr_assignment = FxP_ColonExpression_create(attr, value);
  String *inspection = fxp_inspect(attr_assignment);

  char *expected = "{\"colon_expression\": {"
                      "\"left\": {\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"greeting\"}}}, "
                      "\"right\": {\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}"
                   "}}";

  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_expression_free(attr_assignment);
  string_free(inspection);

  return NULL;
}

char *all_specs() {
  spec_setup("Parser Literal Expression");

  run_spec(test_create_literal);
  run_spec(test_inspect_literal);
  run_spec(test_inspect_lookup);
  run_spec(test_inspect_list);
  run_spec(test_inspect_implicit_method);
  run_spec(test_inspect_method_no_args);
  run_spec(test_inspect_function);
  run_spec(test_inspect_local_assignment);
  run_spec(test_inspect_colon_expression);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
