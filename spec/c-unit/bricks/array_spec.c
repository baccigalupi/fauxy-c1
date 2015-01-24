#include "../../../lib/bricks/array.h"

#include "../lib/spec.h"

char *test_create_array() {
  spec_describe("Create");

  FxB_Array *array = FxB_Array_create(10);

  assert_ints_equal(fxb_array_length(array), 0, "length");
  assert_ints_equal(fxb_array_capacity(array), 10, "capacity");

  fxb_array_free(array);

  return NULL;
}

char *test_fxb_array_push() {
  spec_describe("Push");

  FxB_Array *array = FxB_Array_create(32);
  fxb_array_push(array, "Gerbil");

  assert_ints_equal(fxb_array_length(array), 1, "length");
  assert_strings_equal((char *)(fxb_array_at_index(array, 0)), "Gerbil", "value");

  fxb_array_free(array);

  return NULL;
}

char *test_fxb_array_push_multiple_times() {
  spec_describe("Push many times");

  FxB_Array *array = FxB_Array_create(32);

  fxb_array_push(array, "Gerbil");
  fxb_array_push(array, "Fish");
  fxb_array_push(array, "Human");

  assert_ints_equal(fxb_array_length(array), 3, "length");
  assert_ints_equal(fxb_array_capacity(array), 32, "capacity");

  assert_strings_equal((char *)(fxb_array_at_index(array, 0)), "Gerbil", "value at index 0");
  assert_strings_equal((char *)(fxb_array_at_index(array, 1)), "Fish", "value at index 1");
  assert_strings_equal((char *)(fxb_array_at_index(array, 2)), "Human", "value at index 2");

  fxb_array_free(array);

  return NULL;
}

char *test_fxb_array_push_until_expansion() {
  spec_describe("Push until expansion required");

  FxB_Array *array = FxB_Array_create(32);

  int i;
  char *num;
  for (i = 0; i < 33; i++) {
    num = calloc(4, sizeof(char));
    sprintf(num, "%d", i);
    fxb_array_push(array, num);
  }

  assert_ints_equal(fxb_array_length(array), 33, "length");
  assert_ints_equal(fxb_array_capacity(array), 128, "capacity");

  assert_strings_equal((char *)(fxb_array_at_index(array, 1)), "1", "value at index 1");
  assert_strings_equal((char *)(fxb_array_at_index(array, 30)), "30", "value at index 30");
  assert_strings_equal((char *)(fxb_array_at_index(array, 32)), "32", "value at index 32");

  fxb_array_r_free(array);

  return NULL;
}

char *test_fxb_array_pop() {
  spec_describe("Push until expansion required");

  FxB_Array *array = FxB_Array_create(32);

  fxb_array_push(array, "1");
  fxb_array_push(array, "2");
  fxb_array_push(array, "3");

  char *value = fxb_array_pop(array);

  assert_strings_equal(value, "3", "last value");
  assert_ints_equal(fxb_array_length(array), 2, "length");

  value = fxb_array_pop(array);
  assert_strings_equal(value, "2", "middle value");
  assert_ints_equal(fxb_array_length(array), 1, "length");

  value = fxb_array_pop(array);
  assert_strings_equal(value, "1", "first value");
  assert_ints_equal(fxb_array_length(array), 0, "length");

  fxb_array_free(array);

  return NULL;
}

char *test_fxb_array_set_at_index() {
  spec_describe("set at index, set at index above capacity");

  FxB_Array *array = FxB_Array_create(32);

  fxb_array_set(array, 1, "Gerbil");

  assert_ints_equal(fxb_array_length(array), 2, "length after setting index 1");
  assert_strings_equal((char *)(fxb_array_get(array, 1)), "Gerbil", "value at index 1");

  fxb_array_set(array, 32, "Another Gerbil");
  assert_ints_equal(fxb_array_capacity(array), 128, "capacity after setting above current capacity");
  assert_ints_equal(fxb_array_length(array), 33, "length");
  assert_strings_equal((char *)(fxb_array_get(array, 32)), "Another Gerbil", "value");

  fxb_array_free(array);

  return NULL;
}

char *test_fxb_array_set_at_index_bug() {
  spec_describe("set at index when capactiy starts at 4");

  FxB_Array *array = FxB_Array_create(4);

  fxb_array_set(array, 1, "expressions");

  assert_ints_equal(fxb_array_length(array), 2, "length after setting index at 2");
  fxb_array_set(array, 0, "arguments");
  assert_ints_equal(fxb_array_length(array), 2, "length after setting index at 0");

  fxb_array_free(array);

  return NULL;
}

void *__count_string(void *str) {
  int *length = calloc(1, sizeof(int));
  *length = strlen((char *)str);
  return length;
}

char *test_fxb_array_map() {
  spec_setup("Map");

  FxB_Array *array = FxB_Array_create(2);
  fxb_array_set(array, 0, "1");
  fxb_array_set(array, 1, "two");

  FxB_Array *counts = fxb_array_map(array, __count_string);
  assert_ints_equal(fxb_array_length(array), 2, "length");
  assert_ints_equal(*((int *)fxb_array_get(array, 0)), 1, "value at 0");
  assert_ints_equal(*((int *)fxb_array_get(array, 1)), 3, "value at 0");

  fxb_array_free(array);
  fxb_array_free(counts);

  return NULL;
}

char *all_specs() {
  spec_setup("Brick FxB_Array");

  run_spec(test_create_array);

  run_spec(test_fxb_array_push);
  run_spec(test_fxb_array_push_multiple_times);
  run_spec(test_fxb_array_push_until_expansion);

  run_spec(test_fxb_array_pop);

  run_spec(test_fxb_array_set_at_index);
  run_spec(test_fxb_array_set_at_index_bug);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
