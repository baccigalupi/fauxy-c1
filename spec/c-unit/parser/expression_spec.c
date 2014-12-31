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

  fxp_literal_free(literal);

  return NULL;
}

char *test_inspect_literal() {
  spec_describe("inspecting a literal expression");

  FxP_Bit *bit = FxP_Bit_create(TOKEN_STRING, "\"hello world\"");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);

  String *inspection = fxp_literal_inspect(literal);
  assert_strings_equal(string_value(inspection), "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}", "json");

  fxp_literal_free(literal);
  string_free(inspection);

  return NULL;
}

char *test_inspect_lookup() {
  spec_describe("inspecting a lookup expression");

  FxP_Bit *bit = FxP_Bit_create(TOKEN_ID, "foo");
  FxP_Literal *lookup = FxP_Lookup_create(bit, TOKEN_ID);

  String *inspection = fxp_lookup_inspect(lookup);
  assert_strings_equal(string_value(inspection), "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}}", "json");

  fxp_literal_free(lookup);
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

  String *inspection = fxp_list_inspect(list);
  char *expected = "{\"list\": [\n{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}},\n{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}\n]}";
  assert_strings_equal(string_value(inspection), expected, "json");

  fxp_literal_free(list);
  string_free(inspection);

  return NULL;
}

// char *test_inspect_function() {
//   spec_describe("inspecting a function expression");
//
//   FxP_Bit *bit = FxP_Bit_create(TOKEN_ID, "foo");
//   FxP_Literal *lookup = FxP_Lookup_create(bit, TOKEN_ID);
//
//   String *inspection = fxp_lookup_inspect(lookup);
//   assert_strings_equal(string_value(inspection), "{\"function\": {\"arguments\": [], expressions: []}}", "json");
//
//   fxp_literal_free(lookup);
//   string_free(inspection);
//
//   return NULL;
// }

char *all_specs() {
  spec_setup("Parser Literal Expression");

  run_spec(test_create_literal);
  run_spec(test_inspect_literal);
  run_spec(test_inspect_lookup);
  run_spec(test_inspect_list);
  // run_spec(test_inspect_function);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
