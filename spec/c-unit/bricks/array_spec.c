#include "../../../lib/bricks/array.h"

#include "../lib/spec.h"

char *test_create_array() {
  spec_describe("Create");

  Array *array = Array_create(10);

  assert_ints_equal(array_length(array), 0, "length");
  assert_ints_equal(array_capacity(array), 10, "capacity");

  array_free(array);

  return NULL;
}

char *test_array_push() {
  spec_describe("Push");

  Array *array = Array_create(32);
  array_push(array, "Gerbil");

  assert_ints_equal(array_length(array), 1, "length");
  assert_strings_equal((char *)(array_at_index(array, 0)), "Gerbil", "value");

  array_free(array);

  return NULL;
}

char *test_array_push_multiple_times() {
  spec_describe("Push many times");

  Array *array = Array_create(32);

  array_push(array, "Gerbil");
  array_push(array, "Fish");
  array_push(array, "Human");

  assert_ints_equal(array_length(array), 3, "length");
  assert_ints_equal(array_capacity(array), 32, "capacity");

  assert_strings_equal((char *)(array_at_index(array, 0)), "Gerbil", "value at index 0");
  assert_strings_equal((char *)(array_at_index(array, 1)), "Fish", "value at index 1");
  assert_strings_equal((char *)(array_at_index(array, 2)), "Human", "value at index 2");

  array_free(array);

  return NULL;
}

char *test_array_push_until_expansion() {
  spec_describe("Push until expansion required");

  Array *array = Array_create(32);

  int i;
  char *num;
  for (i = 0; i < 33; i++) {
    num = calloc(4, sizeof(char));
    sprintf(num, "%d", i);
    array_push(array, num);
  }

  assert_ints_equal(array_length(array), 33, "length");
  assert_ints_equal(array_capacity(array), 128, "capacity");

  assert_strings_equal((char *)(array_at_index(array, 1)), "1", "value at index 1");
  assert_strings_equal((char *)(array_at_index(array, 30)), "30", "value at index 30");
  assert_strings_equal((char *)(array_at_index(array, 32)), "32", "value at index 32");

  array_r_free(array);

  return NULL;
}

char *test_array_pop() {
  spec_describe("Push until expansion required");

  Array *array = Array_create(32);

  array_push(array, "1");
  array_push(array, "2");
  array_push(array, "3");

  char *value = array_pop(array);

  assert_strings_equal(value, "3", "last value");
  assert_ints_equal(array_length(array), 2, "length");

  value = array_pop(array);
  assert_strings_equal(value, "2", "middle value");
  assert_ints_equal(array_length(array), 1, "length");

  value = array_pop(array);
  assert_strings_equal(value, "1", "first value");
  assert_ints_equal(array_length(array), 0, "length");

  array_free(array);

  return NULL;
}

char *test_array_set_at_index() {
  spec_describe("Push until expansion required");

  Array *array = Array_create(32);

  array_set(array, 1, "Gerbil");

  assert_ints_equal(array_length(array), 2, "length after setting index 1");
  assert_strings_equal((char *)(array_get(array, 1)), "Gerbil", "value at index 1");

  array_set(array, 32, "Another Gerbil");
  assert_ints_equal(array_capacity(array), 128, "capacity after setting above current capacity");
  assert_ints_equal(array_length(array), 33, "length");
  assert_strings_equal((char *)(array_get(array, 32)), "Another Gerbil", "value");

  array_free(array);

  return NULL;
}

char *all_specs() {
  spec_setup("Brick Array");

  run_spec(test_create_array);

  run_spec(test_array_push);
  run_spec(test_array_push_multiple_times);
  run_spec(test_array_push_until_expansion);

  run_spec(test_array_pop);

  run_spec(test_array_set_at_index);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
