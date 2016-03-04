#include <string.h>
#include <limits.h>

#include "../../../src/parser/_parser.h"
#include "../lib/spec.h"


char *test_string_type_creation() {
  spec_describe("creating bits with string type");
  char *text = calloc(7, sizeof(char));
  strcpy(text, "\"text\"");

  FxP_Bit *bit = FxP_Bit_string_create(text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_STRING, "type");
  assert_strings_equal(fxp_bit_string_value(bit), "text", "value");

  fxp_bit_free(bit);

  return NULL;
}

char *test_integer_type_creation() {
  spec_describe("creating bits with short type");
  char *text = calloc(5, sizeof(char));
  strcpy(text, "42");

  FxP_Bit *bit = FxP_Bit_integer_create(text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_NUMBER, "type");
  assert_ints_equal(fxp_bit_integer_value(bit), (short)42, "value");

  fxp_bit_free(bit);

  return NULL;
}

char *test_float_type_creation() {
  spec_describe("creating bits with float type");
  char *text = calloc(4, sizeof(char));
  strcpy(text, "3.14");

  FxP_Bit *bit = FxP_Bit_decimal_create(text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_NUMBER, "type");
  assert_equal(fxb_bit_double_value(bit), (double)3.14, "value");

  fxp_bit_free(bit);

  return NULL;
}

char *test_exponent_type_creation() {
  spec_describe("creating bits with exponent float type");
  char *text = calloc(4, sizeof(char));
  strcpy(text, "3.1e3");

  FxP_Bit *bit = FxP_Bit_exponent_create(text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_NUMBER, "type");
  assert_equal(fxb_bit_double_value(bit), (double)3.1e3, "value");

  fxp_bit_free(bit);

  return NULL;
}

char *all_specs() {
  spec_setup("Parser Bit");

  run_spec(test_string_type_creation);
  run_spec(test_integer_type_creation);
  run_spec(test_float_type_creation);
  run_spec(test_exponent_type_creation);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
