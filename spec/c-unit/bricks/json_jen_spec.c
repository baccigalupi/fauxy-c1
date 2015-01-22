#include "../../../lib/bricks/string.h"
#include "../../../lib/bricks/array.h"
#include "../../../lib/bricks/json_gen.h"

#include "../lib/spec.h"

char *test_bald_wrapping_pair() {
  spec_describe("bald pairs");
  String *key = String_create("key");
  String *value = String_create("\"value\"");

  String *pair = json_gen_bald_pair(key, value);

  assert_strings_equal(string_value(pair), "\"key\": \"value\"", "wrapped key and value");

  string_free(pair);
  string_free(key);
  string_free(value);

  return NULL;
}

char *test_bald_non_wrapping_pair() {
  String *key = String_create("\"key\"");
  String *value = String_create("\"value\"");

  String *pair = json_gen_bald_pair(key, value);

  assert_strings_equal(string_value(pair), "\"key\": \"value\"", "direct key and value");

  string_free(pair);
  string_free(key);
  string_free(value);

  return NULL;
}

char *test_wrap_pair() {
  spec_describe("joining and wrapping pairs");

  String *key_1 = String_create("\"one\"");
  String *value_1 = String_create("1");
  String *pair_1 = json_gen_bald_pair(key_1, value_1);

  FxB_Array *pairs = FxB_Array_create(1);
  array_push(pairs, pair_1);

  String *json = json_gen_wrap_pairs(pairs);
  assert_strings_equal(string_value(json), "{\"one\": 1}", "one pair");

  string_free(key_1);
  string_free(value_1);
  string_free(pair_1);

  array_free(pairs);

  string_free(json);

  return NULL;
}


char *test_wrap_three_pairs() {
  String *key_1 = String_create("\"one\"");
  String *value_1 = String_create("1");
  String *pair_1 = json_gen_bald_pair(key_1, value_1);

  String *key_2 = String_create("\"two\"");
  String *value_2 = String_create("2");
  String *pair_2 = json_gen_bald_pair(key_2, value_2);

  String *key_3 = String_create("\"three\"");
  String *value_3 = String_create("3");
  String *pair_3 = json_gen_bald_pair(key_3, value_3);

  FxB_Array *pairs = FxB_Array_create(3);
  array_push(pairs, pair_1);
  array_push(pairs, pair_2);
  array_push(pairs, pair_3);

  String *json = json_gen_wrap_pairs(pairs);
  assert_strings_equal(string_value(json), "{\"one\": 1, \"two\": 2, \"three\": 3}", "three pairs");

  string_free(key_1);
  string_free(key_2);
  string_free(key_3);
  string_free(value_1);
  string_free(value_2);
  string_free(value_3);
  string_free(pair_1);
  string_free(pair_2);
  string_free(pair_3);

  array_free(pairs);

  string_free(json);

  return NULL;
}

char *all_specs() {
  spec_setup("Brick Json Generation");

  run_spec(test_bald_wrapping_pair);
  run_spec(test_bald_non_wrapping_pair);
  run_spec(test_wrap_pair);
  run_spec(test_wrap_three_pairs);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
