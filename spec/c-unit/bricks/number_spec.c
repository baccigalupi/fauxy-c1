#include "../../../lib/bricks/number.h"
#include <limits.h>

#include "../lib/spec.h"

char *test_read_short_int() {
  spec_describe("reading a short integer from a string");

  FxB_Number *integer = FxB_Integer_from_string("1");

  assert_ints_equal(fxb_number_type(integer), FXB_INT_SHORT, "type");
  assert_equal(fxb_number_value_short(integer), (short)1, "value");

  return NULL;
}

char *test_read_standard_int() {
  spec_describe("reading a standard integer from a string");

  int number = SHRT_MAX + 1;
  char str_number[100];
  sprintf(str_number, "%d", number);

  FxB_Number *integer = FxB_Integer_from_string(str_number);

  assert_ints_equal(fxb_number_type(integer), FXB_INT_STANDARD, "type");
  assert_equal(fxb_number_value_standard(integer), number, "value");

  return NULL;
}

char *test_read_long_int() {
  spec_describe("reading a long integer from a string");

  long number = (long)INT_MAX + 1;
  char str_number[100];
  sprintf(str_number, "%ld", number);

  FxB_Number *integer = FxB_Integer_from_string(str_number);

  assert_ints_equal(fxb_number_type(integer), FXB_INT_LONG, "type");
  assert_equal(fxb_number_value_long(integer), number, "value");

  return NULL;
}

char *test_small_decimals() {
  spec_describe("reading smaller decimals from a string");

  FxB_Number *decimal = FxB_Decimal_from_string("1.2");

  assert_ints_equal(fxb_number_type(decimal), FXB_DECIMAL_DOUBLE, "type");
  assert_equal(fxb_number_value_double(decimal), (double)1.2, "value");

  return NULL;
}

char *test_big_decimals() {
  spec_describe("reading larger decimals from a string");

  FxB_Number *decimal = FxB_Decimal_from_string("1.234567890123456700");

  assert_ints_equal(fxb_number_type(decimal), FXB_DECIMAL_LDOUBLE, "type");
  double diff = fxb_number_value_ldouble(decimal) - (long double)1.2345678901234567;
  assert_truthy(diff < 1e-17, "value");

  return NULL;
}

char *all_specs() {
  spec_setup("Brick FxB_Number");

  run_spec(test_read_short_int);
  run_spec(test_read_standard_int);
  run_spec(test_read_long_int);

  run_spec(test_small_decimals);
  run_spec(test_big_decimals);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
