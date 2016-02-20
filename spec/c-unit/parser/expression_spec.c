#include <string.h>

#include "../../../src/parser/_parser.h"
#include "../lib/spec.h"

char *test_create_literal() {
  spec_describe("creating literal expression from bit");

  FxP_Bit *bit = FxP_Bit_string_create("\"hello world\"");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);

  assert_ints_equal(fxp_literal_type(literal), TOKEN_STRING, "type");
  assert_equal(fxp_literal_bit(literal), bit, "bit value");

  fxp_expression_free(literal);

  return NULL;
}

char *test_inspect_literal_with_bit() {
  spec_describe("inspecting a literal expression with bit");

  FxP_Bit *bit = FxP_Bit_string_create("\"hello world\"");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);

  char *inspection = fxp_inspect(literal);
  char *expected = "{\n"
  "  \"literal\": {\n"
  "    \"bit\": {\n"
  "      \"STRING\": \"hello world\"\n"
  "    },\n"
  "    \"class\": \"String\"\n"
  "  }\n"
  "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(literal);
  free(inspection);

  return NULL;
}

char *test_inspect_literal_without_bit() {
  spec_describe("inspecting a literal expression without bit");

  FxP_Literal *literal = FxP_Literal_create(NULL, TOKEN_TRUE);

  char *inspection = fxp_inspect(literal);
  char *expected = "{\n"
    "  \"literal\": {\n"
    "    \"value\": true,\n"
    "    \"class\": \"Boolean\"\n"
    "  }\n"
    "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(literal);
  free(inspection);

  return NULL;
}


char *test_inspect_lookup() {
  spec_describe("inspecting a lookup expression");

  FxP_Bit *bit = FxP_Bit_string_create("foo");
  FxP_Literal *lookup = FxP_Lookup_create(bit, TOKEN_ID);

  char *inspection = fxp_inspect(lookup);
  char *expected = "{\n"
    "  \"lookup\": {\n"
    "    \"type\": \"Identifier\",\n"
    "    \"bit\": {\n"
    "      \"STRING\": \"foo\"\n"
    "    }\n"
    "  }\n"
    "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(lookup);
  free(inspection);

  return NULL;
}

char *test_inspect_list() {
  spec_describe("inspecting a list expression");

  FxP_Bit     *bit_1 = FxP_Bit_string_create("foo");
  FxP_Literal *arg_1 = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_string_create("\"hello world\"");
  FxP_Literal *arg_2 = FxP_Literal_create(bit_2, TOKEN_STRING);

  FxP_List    *list = FxP_List_create_double(arg_1, arg_2);

  char *inspection = fxp_inspect(list);
  char *expected = "{\n"
    "  \"list\": [\n"
    "    {\n"
    "      \"lookup\": {\n"
    "        \"type\": \"Identifier\",\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"foo\"\n"
    "        }\n"
    "      }\n"
    "    },\n"
    "    {\n"
    "      \"literal\": {\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"hello world\"\n"
    "        },\n"
    "        \"class\": \"String\"\n"
    "      }\n"
    "    }\n"
    "  ]\n"
    "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(list);
  free(inspection);

  return NULL;
}

char *test_inspect_implicit_method() {
  spec_describe("inspecting an implicit method call");

  FxP_Bit *bit_1 = FxP_Bit_string_create("print");
  FxP_Literal *message = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit *bit_2 = FxP_Bit_string_create("\"hello world\"");
  FxP_Literal *arg = FxP_Literal_create(bit_2, TOKEN_STRING);

  // print "hello world"
  FxP_MethodCall*method = FxP_MethodCall_create_implicit(message, arg);
  char *inspection = fxp_inspect(method);
  char *expected = "{\n"
    "  \"method_call\": {\n"
    "    \"message\": {\n"
    "      \"lookup\": {\n"
    "        \"type\": \"Identifier\",\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"print\"\n"
    "        }\n"
    "      }\n"
    "    },\n"
    "    \"arguments\": [\n"
    "      {\n"
    "        \"literal\": {\n"
    "          \"bit\": {\n"
    "            \"STRING\": \"hello world\"\n"
    "          },\n"
    "          \"class\": \"String\"\n"
    "        }\n"
    "      }\n"
    "    ]\n"
    "  }\n"
    "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(method);
  free(inspection);

  return NULL;
}

char *test_inspect_method_no_args() {
  spec_describe("inspecting a method call with no args");

  FxP_Bit *bit_1 = FxP_Bit_string_create("printer");
  FxP_Literal *receiver = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit *bit_2 = FxP_Bit_string_create("print");
  FxP_Literal *message = FxP_Lookup_create(bit_2, TOKEN_ID);

  // printer.print
  FxP_MethodCall*method = FxP_MethodCall_create_no_args(receiver, message);

  char *inspection = fxp_inspect(method);
  char *expected = "{\n"
    "  \"method_call\": {\n"
    "    \"receiver\": {\n"
    "      \"lookup\": {\n"
    "        \"type\": \"Identifier\",\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"printer\"\n"
    "        }\n"
    "      }\n"
    "    },\n"
    "    \"message\": {\n"
    "      \"lookup\": {\n"
    "        \"type\": \"Identifier\",\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"print\"\n"
    "        }\n"
    "      }\n"
    "    }\n"
    "  }\n"
    "}";
  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(method);
  free(inspection);

  return NULL;
}

char *test_inspect_function() {
  spec_describe("inspecting a function with arguments");

  // arguments
  FxP_Bit     *bit_1 = FxP_Bit_string_create("foo");
  FxP_Literal *arg_1 = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_string_create("bar");
  FxP_Literal *arg_2 = FxP_Lookup_create(bit_2, TOKEN_ID);

  FxP_List    *arguments = FxP_List_create_double(arg_1, arg_2);
  fxp_expression_type(arguments) = FX_ST_FUNCTION_DEFINITION_ARGUMENTS;

  // expressions
  FxP_Expressions *expressions = FxP_Expressions_create();

  // function
  FxP_FunctionDefinition *function = FxP_FunctionDefinition_create(arguments);
  fxp_function_definition_set_expressions(function, expressions);

  char *inspection = fxp_inspect(function);
  char *expected = "{\n"
    "  \"function_definition\": {\n"
    "    \"arguments\": {\n"
    "      \"function_arguments\": [\n"
    "        {\n"
    "          \"lookup\": {\n"
    "            \"type\": \"Identifier\",\n"
    "            \"bit\": {\n"
    "              \"STRING\": \"foo\"\n"
    "            }\n"
    "          }\n"
    "        },\n"
    "        {\n"
    "          \"lookup\": {\n"
    "            \"type\": \"Identifier\",\n"
    "            \"bit\": {\n"
    "              \"STRING\": \"bar\"\n"
    "            }\n"
    "          }\n"
    "        }\n"
    "      ]\n"
    "    },\n"
    "    \"expressions\": []\n"
    "  }\n"
    "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(function);
  free(inspection);

  return NULL;
}

char *test_inspect_colon_expression() {
  spec_describe("inspecting colon expression");

  // arguments
  FxP_Bit     *bit_1 = FxP_Bit_string_create("greeting");
  FxP_Literal *attr = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_string_create("\"hello world\"");
  FxP_Literal *value = FxP_Literal_create(bit_2, TOKEN_STRING);

  FxP_Expression *attr_assignment = FxP_ColonExpression_create(attr, value);
  char *inspection = fxp_inspect(attr_assignment);

  char *expected = "{\n"
    "  \"colon_expression\": {\n"
    "    \"left\": {\n"
    "      \"lookup\": {\n"
    "        \"type\": \"Identifier\",\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"greeting\"\n"
    "        }\n"
    "      }\n"
    "    },\n"
    "    \"right\": {\n"
    "      \"literal\": {\n"
    "        \"bit\": {\n"
    "          \"STRING\": \"hello world\"\n"
    "        },\n"
    "        \"class\": \"String\"\n"
    "      }\n"
    "    }\n"
    "  }\n"
    "}";

  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(attr_assignment);
  free(inspection);

  return NULL;
}

char *test_inspect_expressions() {
  spec_describe("inspecting expressions");

  FxP_Bit     *bit_1 = FxP_Bit_string_create("greeting");
  FxP_Literal *lookup = FxP_Lookup_create(bit_1, TOKEN_ID);

  FxP_Bit     *bit_2 = FxP_Bit_string_create("\"hello world\"");
  FxP_Literal *string = FxP_Literal_create(bit_2, TOKEN_STRING);

  FxP_Expressions *expressions = FxP_Expressions_create();
  fxp_expression_push(expressions, lookup);
  fxp_expression_push(expressions, string);

  char *inspection = fxp_inspect(expressions);
  char *expected = "{\n"
"  \"expressions\": [\n"
"    {\n"
"      \"lookup\": {\n"
"        \"type\": \"Identifier\",\n"
"        \"bit\": {\n"
"          \"STRING\": \"greeting\"\n"
"        }\n"
"      }\n"
"    },\n"
"    {\n"
"      \"literal\": {\n"
"        \"bit\": {\n"
"          \"STRING\": \"hello world\"\n"
"        },\n"
"        \"class\": \"String\"\n"
"      }\n"
"    }\n"
"  ]\n"
"}";
  assert_strings_equal(inspection, expected, "json");

  fxp_expression_free(expressions);
  free(inspection);

  return NULL;
}

char *all_specs() {
  spec_setup("Parser Literal Expression");

  run_spec(test_create_literal);
  run_spec(test_inspect_literal_with_bit);
  run_spec(test_inspect_literal_without_bit);
  run_spec(test_inspect_lookup);
  run_spec(test_inspect_list);
  run_spec(test_inspect_implicit_method);
  run_spec(test_inspect_method_no_args);
  run_spec(test_inspect_function);
  run_spec(test_inspect_colon_expression);
  run_spec(test_inspect_expressions);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
