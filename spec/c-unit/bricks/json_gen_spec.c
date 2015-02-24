#include "../../../lib/bricks/_bricks.h"
#include "../lib/spec.h"

char *test_bald_wrapping_pair() {
  spec_describe("bald pairs");
  FxB_String *key = FxB_String_create("key");
  FxB_String *value = FxB_String_create("\"value\"");

  FxB_String *pair = fxb_json_gen_bald_pair(key, value);

  assert_strings_equal(fxb_string_value(pair), "\"key\": \"value\"", "wrapped key and value");

  fxb_string_free(pair);
  fxb_string_free(key);
  fxb_string_free(value);

  return NULL;
}

char *test_bald_non_wrapping_pair() {
  FxB_String *key = FxB_String_create("\"key\"");
  FxB_String *value = FxB_String_create("\"value\"");

  FxB_String *pair = fxb_json_gen_bald_pair(key, value);

  assert_strings_equal(fxb_string_value(pair), "\"key\": \"value\"", "direct key and value");

  fxb_string_free(pair);
  fxb_string_free(key);
  fxb_string_free(value);

  return NULL;
}

char *test_wrap_pair() {
  spec_describe("joining and wrapping pairs");

  FxB_String *key_1 = FxB_String_create("\"one\"");
  FxB_String *value_1 = FxB_String_create("1");
  FxB_String *pair_1 = fxb_json_gen_bald_pair(key_1, value_1);

  FxB_Array *pairs = FxB_Array_create(1);
  fxb_array_push(pairs, pair_1);

  FxB_String *json = fxb_json_gen_wrap_pairs(pairs);
  assert_strings_equal(fxb_string_value(json), "{\"one\": 1}", "one pair");

  fxb_string_free(key_1);
  fxb_string_free(value_1);
  fxb_string_free(pair_1);

  fxb_array_free(pairs);

  fxb_string_free(json);

  return NULL;
}


char *test_wrap_three_pairs() {
  FxB_String *key_1 = FxB_String_create("\"one\"");
  FxB_String *value_1 = FxB_String_create("1");
  FxB_String *pair_1 = fxb_json_gen_bald_pair(key_1, value_1);

  FxB_String *key_2 = FxB_String_create("\"two\"");
  FxB_String *value_2 = FxB_String_create("2");
  FxB_String *pair_2 = fxb_json_gen_bald_pair(key_2, value_2);

  FxB_String *key_3 = FxB_String_create("\"three\"");
  FxB_String *value_3 = FxB_String_create("3");
  FxB_String *pair_3 = fxb_json_gen_bald_pair(key_3, value_3);

  FxB_Array *pairs = FxB_Array_create(3);
  fxb_array_push(pairs, pair_1);
  fxb_array_push(pairs, pair_2);
  fxb_array_push(pairs, pair_3);

  FxB_String *json = fxb_json_gen_wrap_pairs(pairs);
  assert_strings_equal(fxb_string_value(json), "{\"one\": 1, \"two\": 2, \"three\": 3}", "three pairs");

  fxb_string_free(key_1);
  fxb_string_free(key_2);
  fxb_string_free(key_3);
  fxb_string_free(value_1);
  fxb_string_free(value_2);
  fxb_string_free(value_3);
  fxb_string_free(pair_1);
  fxb_string_free(pair_2);
  fxb_string_free(pair_3);

  fxb_array_free(pairs);

  fxb_string_free(json);

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
