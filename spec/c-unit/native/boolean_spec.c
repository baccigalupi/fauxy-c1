#include "../../../lib/parser/tokens.h"
#include "../../../lib/interpreter/pool.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/native/boolean_methods.h"
#include "../lib/spec.h"

#define create_config() FxB_HashMap_create(1)

FxI_Pool *setup_test_boolean_pool() {
  FxB_HashMap *config = create_config();
  FxI_Pool *pool = FxI_Pool_create(config);

  FxP_Expression *false_literal = FxP_Literal_create(NULL, TOKEN_FALSE);
  FxN_Object *false_object = FxN_Boolean_create(pool, false_literal);

  FxP_Expression *true_literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  FxN_Object *true_object = FxN_Boolean_create(pool, true_literal);

  fxi_literal_set(pool, FALSE_KEY, false_object);
  fxi_literal_set(pool, TRUE_KEY, true_object);

  return pool;
}

char *test_boolean_not_value() {
  spec_describe("not booleans");

  FxB_HashMap *config = create_config();
  FxI_Pool *pool = setup_test_boolean_pool();

  FxN_Object *true_value = fxi_literal_get(pool, TRUE_KEY);
  FxN_Object *false_value = fxi_literal_get(pool, FALSE_KEY);

  assert_equal(false_value, fxn_boolean_not(true_value), "!true is false");
  assert_equal(true_value, fxn_boolean_not(false_value), "!false is true");

  return NULL;
}

char *all_specs() {
  spec_setup("Base Type: Boolean methods");

  run_spec(test_boolean_not_value);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
