#include "../../../lib/bricks/number.h"

#include "../lib/spec.h"

char *test_read_short_int() {
  spec_describe("reading a short integer from a string");

  FxB_Integer *integer = FxB_Integer_from_string("1");

  assert_ints_equal(fxb_integer_type(integer), FXB_INT_SHORT, "type");
  assert_equal(fxb_integer_value_short(integer), (short)1, "value");

  return NULL;
}

char *test_read_standard_int() {
  spec_describe("reading a standard integer from a string");

  int number = SHRT_MAX + 1;
  char str_number[100];
  sprintf(str_number, "%d", number);

  FxB_Integer *integer = FxB_Integer_from_string(str_number);

  assert_ints_equal(fxb_integer_type(integer), FXB_INT_STANDARD, "type");
  assert_equal(fxb_integer_value_standard(integer), number, "value");

  return NULL;
}

char *test_read_long_int() {
  spec_describe("reading a long integer from a string");

  long number = (long)INT_MAX + 1;
  char str_number[100];
  sprintf(str_number, "%ld", number);

  FxB_Integer *integer = FxB_Integer_from_string(str_number);

  assert_ints_equal(fxb_integer_type(integer), FXB_INT_LONG, "type");
  assert_equal(fxb_integer_value_long(integer), number, "value");

  return NULL;
}

char *all_specs() {
  spec_setup("Brick FxB_Integer");

  run_spec(test_read_short_int);
  run_spec(test_read_standard_int);
  run_spec(test_read_long_int);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
