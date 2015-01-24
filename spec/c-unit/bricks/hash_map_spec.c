#include "../../../lib/bricks/hash_map.h"
#include "../../../lib/bricks/list.h"

#include "../lib/spec.h"

char *test_create_hash() {
  spec_describe("Create");

  FxB_HashMap *hash_map = FxB_HashMap_create(100);

  assert_ints_equal(fxb_hash_map_capacity(hash_map), 100, "capacity");
  assert_ints_equal(fxb_hash_map_length(hash_map), 0,  "length");
  assert_ints_equal(fxb_array_capacity(fxb_hash_map_values(hash_map)), 100, "values capacity");
  assert_ints_equal(fxb_array_length(fxb_hash_map_values(hash_map)), 0, "values length");

  fxb_hash_map_free(hash_map);
  return NULL;
}

char *test_get_value_from_empty() {
  spec_describe("Getting values from empty hash_map");

  FxB_HashMap *hash_map = FxB_HashMap_create(10);
  FxB_String *key = FxB_String_create("key");

  assert_equal(fxb_hash_map_get(hash_map, key), NULL, "return NULL");

  string_free(key);
  fxb_hash_map_free(hash_map);

  return NULL;
}

char *test_set_value() {
  spec_describe("Setting and getting value");

  FxB_HashMap *hash_map = FxB_HashMap_create(10);
  FxB_String *key = FxB_String_create("key");
  FxB_String *value = FxB_String_create("value");

  fxb_hash_map_set(hash_map, key, value);

  assert_equal(fxb_hash_map_get(hash_map, key), value, "value same");

  string_free(key);
  string_free(value);
  fxb_hash_map_free(hash_map);

  return NULL;
}

char *test_reset_value() {
  spec_describe("Setting and getting value");

  FxB_HashMap *hash_map = FxB_HashMap_create(10);
  FxB_String *key = FxB_String_create("key");
  FxB_String *value_1 = FxB_String_create("value");
  FxB_String *value_2 = FxB_String_create("another value");

  fxb_hash_map_set(hash_map, key, value_1);
  fxb_hash_map_set(hash_map, key, value_2);

  assert_equal(fxb_hash_map_get(hash_map, key), value_2, "value same");
  int index = fxb_hash_map_index_for_key(hash_map, key);
  assert_ints_equal(fxb_list_length((FxB_List *)fxb_hash_map_list_at_index(hash_map, index)), 1, "no duplicates for key in list");

  string_free(key);
  string_free(value_1);
  string_free(value_2);
  fxb_hash_map_free(hash_map);

  return NULL;
}

char *all_specs() {
  spec_setup("Brick FxB_Hash");

  run_spec(test_create_hash);
  run_spec(test_get_value_from_empty);
  run_spec(test_set_value);
  run_spec(test_reset_value);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
