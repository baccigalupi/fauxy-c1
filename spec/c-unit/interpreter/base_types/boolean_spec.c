#include "../../../../lib/parser/tokens.h"
#include "../../../../lib/interpreter/pool.h"
#include "../../../../lib/interpreter/object.h"
#include "../../../../lib/interpreter/base_types/boolean.h"
#include "../../lib/spec.h"

FxI_Pool *setup_test_boolean_pool() {
  FxI_Pool *pool = FxI_Pool_create(2, 1, 1);

  FxP_Expression *false_literal = FxP_Literal_create(NULL, TOKEN_FALSE);
  FxN_Object *false_object = FxN_Boolean_create(pool, false_literal);

  FxP_Expression *true_literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  FxN_Object *true_object = FxN_Boolean_create(pool, true_literal);

  fxi_literal_set(pool, "false", false_object);
  fxi_literal_set(pool, "true", true_object);

  return pool;
}

char *test_boolean_truthiness() {
  spec_describe("truthines of booleans");

  FxI_Pool *pool = setup_test_boolean_pool();

  FxN_Object *boolean = fxi_literal_get(pool, "true");
  assert_equal(boolean, fxn_boolean_is_truthy(boolean), "true object returns self");

  boolean = fxi_literal_get(pool, "false");
  assert_equal(boolean, fxn_boolean_is_truthy(boolean), "false object returns self");

  return NULL;
}

char *test_boolean_not_value() {
  spec_describe("truthines of booleans");

  FxI_Pool *pool = setup_test_boolean_pool();

  FxN_Object *true_value = fxi_literal_get(pool, "true");
  FxN_Object *false_value = fxi_literal_get(pool, "false");

  assert_equal(false_value, fxn_boolean_not(true_value), "!true is false");
  assert_equal(true_value, fxn_boolean_not(false_value), "!false is true");

  return NULL;
}

char *all_specs() {
  spec_setup("Base Type: Boolean methods");

  run_spec(test_boolean_truthiness);
  run_spec(test_boolean_not_value);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);



