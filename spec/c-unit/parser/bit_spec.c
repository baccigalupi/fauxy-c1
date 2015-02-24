#include <string.h>
#include <limits.h>

#include "../../../lib/parser/_parser.h"
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
  assert_ints_equal(fxb_bit_short_int_value(bit), (short)42, "value");

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

char *test_integer_inspection() {
  spec_describe("inspecting small bit integers");
  char *text = calloc(9, sizeof(char));
  strcpy(text, "23");

  FxP_Bit *bit = FxP_Bit_integer_create(text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"INTEGER\": 23}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *test_long_integer_inspection() {
  spec_describe("inspecting large bit integers");
  char *text = calloc(9, sizeof(char));
  strcpy(text, "23004567");

  FxP_Bit *bit = FxP_Bit_integer_create(text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"INTEGER\": 23004567}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *test_float_inspection() {
  spec_describe("inspecting bit floats");
  char *text = calloc(9, sizeof(char));
  strcpy(text, "230.0456");

  FxP_Bit *bit = FxP_Bit_decimal_create(text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"DECIMAL\": 230.046}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *test_exponent_inspection() {
  spec_describe("inspecting bit floats");
  char *text = calloc(9, sizeof(char));
  strcpy(text, "1.4e-3");

  FxP_Bit *bit = FxP_Bit_exponent_create(text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"DECIMAL\": 1.4e-03}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *all_specs() {
  spec_setup("Parser Bit");

  run_spec(test_string_type_creation);
  run_spec(test_integer_type_creation);
  run_spec(test_float_type_creation);
  run_spec(test_exponent_type_creation);

  run_spec(test_integer_inspection);
  run_spec(test_long_integer_inspection);
  run_spec(test_float_inspection);
  run_spec(test_exponent_inspection);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
