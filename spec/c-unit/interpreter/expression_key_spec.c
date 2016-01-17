#include "helpers.h"

char *test_true_key() {
  spec_describe("true");

  FxP_Literal *exp = FxP_Literal_create(NULL, TOKEN_TRUE);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "258", "key is correct");

  return NULL;
}

char *test_false_key() {
  spec_describe("false");

  FxP_Literal *exp = FxP_Literal_create(NULL, TOKEN_FALSE);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "259", "key is correct");

  return NULL;
}

char *test_string_key() {
  spec_describe("string");

  FxP_Bit *bit = FxP_Bit_string_create("Hello, world! How are you today!");
  FxP_Literal *exp = FxP_Literal_create(bit, TOKEN_STRING);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "266-Hello, world! How are you today!", "key is correct");

  return NULL;
}

char *test_eval_string_key() {
  spec_describe("eval string");

  FxP_Bit *bit = FxP_Bit_string_create("Hello, world! How are you today!");
  FxP_Literal *exp = FxP_Literal_create(bit, TOKEN_EVAL_STRING);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "267-Hello, world! How are you today!", "key is correct");

  return NULL;
}

char *test_large_integer_key() {
  spec_describe("large integer");

  FxP_Bit *bit = FxP_Bit_integer_create("1234567890123456789");
  FxP_Literal *exp = FxP_Literal_create(bit, TOKEN_INTEGER);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "268-1234567890123456789", "key is correct");

  return NULL;
}

char *test_large_decimal_key() {
  spec_describe("large decimal");

  FxP_Bit *bit = FxP_Bit_decimal_create("123456789.0123456789");
  FxP_Literal *exp = FxP_Literal_create(bit, TOKEN_FLOAT);
  char *key = fxi_literal_key(exp);

  assert_equal(key, NULL, "no key provided");

  return NULL;
}

char *test_class_key() {
  spec_describe("class");

  FxP_Bit *bit = FxP_Bit_string_create("MyClass");
  FxP_Lookup  *exp = FxP_Lookup_create(bit, TOKEN_CLASS_ID);
  char *key = fxi_lookup_key(exp);

  assert_strings_equal(key, "MyClass", "key is correct");

  return NULL;
}

char *test_identifier_key() {
  spec_describe("identifier");

  FxP_Bit *bit = FxP_Bit_string_create("x");
  FxP_Lookup  *exp = FxP_Lookup_create(bit, TOKEN_ID);
  char *key = fxi_lookup_key(exp);

  assert_strings_equal(key, "x", "key is correct");

  return NULL;
}

char *all_specs() {
  spec_setup("Interpreter Literal keys");

  // literals
  run_spec(test_true_key);
  run_spec(test_false_key);
  run_spec(test_string_key);
  run_spec(test_eval_string_key);
  run_spec(test_large_integer_key);
  run_spec(test_large_decimal_key);

  // classes
  run_spec(test_class_key);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
