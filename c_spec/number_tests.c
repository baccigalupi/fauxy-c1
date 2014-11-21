#include "../../lib/bricks/number.h"
#include "../../lib/bricks/bricks.h"

#include "../lib/spec.h"


char *test_number_create_as_float() {
  spec_describe("Create float");
  Number *number = Number_create("1.45");
  assert_ints_equal(number_type(number), FloatType,    "type");
  assert_floats_equal(number_value(number), (FLOAT)1.45, "value");

  number_destroy(number);

  return NULL;
}

char *test_number_create_as_int() {
  spec_describe("Create int");
  Number *number = Number_create("145");
  assert_ints_equal(number_type(number), IntegerType, "type");
  assert_equal(number_value(number), (INT)145,   "value");

  number_destroy(number);

  return NULL;
}

char *test_convert_to_same_type() {
  spec_describe("Convert to same type");
  Number *number = Number_create("145");
  number_convert(number, IntegerType);

  assert_ints_equal(number_type(number), IntegerType, "type");
  assert_equal(number_value(number), (INT)145,   "value");

  number_destroy(number);

  number = Number_create("3.14");
  number_convert(number, FloatType);

  assert_ints_equal(number_type(number), FloatType,     "type");
  assert_floats_equal(number_value(number), (FLOAT)3.14,  "value");

  number_destroy(number);

  return NULL;
}

char *test_convert_to_int() {
  spec_describe("Convert to int");
  Number *number = Number_create("3.14");
  number_convert(number, IntegerType);

  assert_ints_equal(number_type(number), (int)IntegerType,  "change type");
  assert_equal(number_value(number), (INT)3,           "change value");

  number_destroy(number);
  return NULL;
}

char *test_convert_to_float() {
  spec_describe("Convert to float");
  Number *number = Number_create("3");
  number_convert(number, FloatType);

  assert_ints_equal(number_type(number), (int)FloatType,  "change type");
  assert_floats_equal(number_value(number), (FLOAT)3.0,  "change value");

  number_destroy(number);

  return NULL;
}

char *all_specs() {
  spec_setup("Brick Number");

  run_spec(test_number_create_as_float);
  run_spec(test_number_create_as_int);
  run_spec(test_convert_to_same_type);
  run_spec(test_convert_to_int);
  run_spec(test_convert_to_float);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
