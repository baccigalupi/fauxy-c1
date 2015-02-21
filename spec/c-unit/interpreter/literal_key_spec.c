#include "../../../lib/interpreter/literal.h"
#include "../../../lib/parser/expressions.h"
#include "../../../lib/parser/tokens.h"
#include "../lib/spec.h"

char *test_nil_key() {
  spec_describe("nil");

  FxP_Literal *nil_exp = FxP_Literal_create(NULL, TOKEN_NIL);
  char *key = fxi_literal_key(nil_exp);

  assert_strings_equal(key, "260", "key is correct");

  return NULL;
}

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

  assert_strings_equal(key, "267-Hello, world! How are you today!", "key is correct");

  return NULL;
}

char *test_eval_string_key() {
  spec_describe("eval string");

  FxP_Bit *bit = FxP_Bit_string_create("Hello, world! How are you today!");
  FxP_Literal *exp = FxP_Literal_create(bit, TOKEN_EVAL_STRING);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "268-Hello, world! How are you today!", "key is correct");

  return NULL;
}

char *test_large_integer_key() {
  spec_describe("large integer");

  FxP_Bit *bit = FxP_Bit_integer_create("1234567890123456789");
  FxP_Literal *exp = FxP_Literal_create(bit, TOKEN_INTEGER);
  char *key = fxi_literal_key(exp);

  assert_strings_equal(key, "269-1234567890123456789", "key is correct");

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

char *all_specs() {
  spec_setup("Interpreter Literal keys");

  run_spec(test_nil_key);
  run_spec(test_true_key);
  run_spec(test_false_key);
  run_spec(test_string_key);
  run_spec(test_eval_string_key);
  run_spec(test_large_integer_key);
  run_spec(test_large_decimal_key);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
