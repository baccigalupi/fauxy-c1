#include <string.h>

#include "../../../lib/parser/bit.h"
#include "../lib/spec.h"


char *test_typing_token_string() {
  spec_describe("token conversion");
  int token_type = TOKEN_STRING;
  int bit_type = FxP_Bit_bit_type(token_type, true);

  assert_equal(bit_type, FX_BIT_STRING, "type string");

  return NULL;
}

char *test_typing_token_eval_string() {
  int token_type = TOKEN_EVAL_STRING;
  int bit_type = FxP_Bit_bit_type(token_type, false);

  assert_equal(bit_type, FX_BIT_STRING, "type eval string");

  return NULL;
}

char *test_typing_token_float() {
  int token_type = TOKEN_FLOAT;
  int bit_type = FxP_Bit_bit_type(token_type, true);

  assert_equal(bit_type, FX_BIT_FLOAT, "type float");

  return NULL;
}

char *test_typing_token_int() {
  int token_type = TOKEN_INTEGER;
  int bit_type = FxP_Bit_bit_type(token_type, true);

  assert_equal(bit_type, FX_BIT_SHORT, "type integer");

  return NULL;
}

char *test_string_type_creation() {
  spec_describe("creating bits with string type");
  int token_type = TOKEN_STRING;
  char *text = calloc(7, sizeof(char));
  strcpy(text, "\"text\"");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_STRING, "type");
  assert_strings_equal(fxp_bit_string_value(bit), "text", "value");

  fxp_bit_free(bit);

  return NULL;
}

char *test_small_integer_type_creation() {
  spec_describe("creating bits with short type");
  int token_type = TOKEN_INTEGER;
  char *text = calloc(5, sizeof(char));
  strcpy(text, "42");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_SHORT, "type");
  assert_ints_equal(fxp_bit_short_value(bit), 42, "value");

  fxp_bit_free(bit);

  return NULL;
}

char *test_large_integer_type_creation() {
  spec_describe("creating bits with long type");
  int token_type = TOKEN_INTEGER;
  char *text = calloc(9, sizeof(char));
  strcpy(text, "4200346");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_LONG, "type");
  assert_ints_equal(fxp_bit_long_value(bit), 4200346, "value");

  fxp_bit_free(bit);

  return NULL;
}

char *test_float_type_creation() {
  spec_describe("creating bits with float type");
  int token_type = TOKEN_FLOAT;
  char *text = calloc(4, sizeof(char));
  strcpy(text, "3.14");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  assert_ints_equal(fxp_bit_type(bit), FX_BIT_FLOAT, "type");
  assert_floats_equal(fxp_bit_float_value(bit), (double)3.14, "value");

  fxp_bit_free(bit);

  return NULL;
}

// not working right now, lots of overflow checking needed
// ... later for number allocations

// char *test_long_float_type_creation() {
//   spec_describe("creating bits with long float type");
//   int token_type = TOKEN_FLOAT;
//   char *text = calloc(4, sizeof(char));
//   strcpy(text, "27.89486");
//
//   FxP_Bit *bit = FxP_Bit_create(token_type, text);
//   free(text);
//
//   assert_ints_equal(fxp_bit_type(bit), FX_BIT_LONG_FLOAT, "type");
//   printf("%lu == %Lu: %d", fxp_bit_long_float_value(bit), (long double)27.89486, fxp_bit_long_float_value(bit) == (long double)27.89486);
//   assert_floats_equal(fxp_bit_long_float_value(bit), (long double)27.89486, "value");
//
//   return NULL;
// }

char *test_integer_inspection() {
  spec_describe("inspecting small bit integers");
  int token_type = TOKEN_INTEGER;
  char *text = calloc(9, sizeof(char));
  strcpy(text, "23");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"INTEGER\": 23}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *test_long_integer_inspection() {
  spec_describe("inspecting large bit integers");
  int token_type = TOKEN_INTEGER;
  char *text = calloc(9, sizeof(char));
  strcpy(text, "23004567");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"INTEGER\": 2.3e+07}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *test_float_inspection() {
  spec_describe("inspecting bit floats");
  int token_type = TOKEN_FLOAT;
  char *text = calloc(9, sizeof(char));
  strcpy(text, "230.0456");

  FxP_Bit *bit = FxP_Bit_create(token_type, text);
  free(text);

  FxB_String *inspection = fxp_bit_inspect(bit);

  assert_strings_equal(fxb_string_value(inspection), "{\"FLOAT\": 230.05}", "representation");

  fxp_bit_free(bit);

  return NULL;
}

char *all_specs() {
  spec_setup("Parser Bit");

  run_spec(test_typing_token_string);
  run_spec(test_typing_token_eval_string);
  run_spec(test_typing_token_float);
  run_spec(test_typing_token_int);

  run_spec(test_string_type_creation);
  run_spec(test_small_integer_type_creation);
  run_spec(test_large_integer_type_creation);
  run_spec(test_float_type_creation);
  // run_spec(test_long_float_type_creation);

  run_spec(test_integer_inspection);
  run_spec(test_long_integer_inspection);
  run_spec(test_float_inspection);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
