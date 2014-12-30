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
  assert_strings_equal(string_value(inspection), "{\"literal\": {\"class\": \"String\", \"bit\": {\"STRING\": \"hello worl...\"}}}", "String type");

  fxp_literal_free(literal);
  string_free(inspection);

  return NULL;
}

char *test_inspect_lookup() {
  spec_describe("inspecting a lookup expression");

  FxP_Bit *bit = FxP_Bit_create(TOKEN_ID, "foo");
  FxP_Literal *lookup = FxP_Lookup_create(bit, TOKEN_ID);

  String *inspection = fxp_lookup_inspect(lookup);
  assert_strings_equal(string_value(inspection), "{\"lookup\": {\"type\": \"Identifier\", \"bit\": {\"STRING\": \"foo\"}}}", "Identifier type");

  fxp_literal_free(lookup);
  string_free(inspection);

  return NULL;
}

char *all_specs() {
  spec_setup("Parser Literal Expression");

  run_spec(test_create_literal);
  run_spec(test_inspect_literal);
  run_spec(test_inspect_lookup);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
