#include <string.h>

#include "../../../lib/parser/bit.h"
#include "../../../lib/parser/expressions.h"
#include "../lib/spec.h"

char *test_create_literal() {
  spec_describe("creating literal expression from bit");

  FxBit *bit = FxBit_create(TOKEN_STRING, "hello world");
  FxLiteral *literal = FxLiteral_create(bit, TOKEN_STRING);

  assert_ints_equal(fx_literal_type(literal), TOKEN_STRING, "type");
  assert_equal(fx_literal_bit(literal), bit, "bit value");

  fx_literal_free(literal);

  return NULL;
}

char *test_inspect_literal() {
  spec_describe("inspecting a literal expression");

  FxBit *bit = FxBit_create(TOKEN_STRING, "hello world");
  FxLiteral *literal = FxLiteral_create(bit, TOKEN_STRING);

  String *inspection = fx_literal_inspect(literal);
  assert_strings_equal(string_value(inspection), "(literal: String, <STRING: \"hello worl...\">)", "String type");

  fx_literal_free(literal);
  string_free(inspection);

  return NULL;
}

char *test_inspect_lookup() {
  spec_describe("inspecting a lookup expression");

  FxBit *bit = FxBit_create(TOKEN_ID, "foo");
  FxLiteral *lookup = FxLiteral_create(bit, TOKEN_ID);

  String *inspection = fx_lookup_inspect(lookup);
  assert_strings_equal(string_value(inspection), "(lookup: Identifier, <STRING: \"foo\">)", "Identifier type");

  fx_literal_free(lookup);
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
