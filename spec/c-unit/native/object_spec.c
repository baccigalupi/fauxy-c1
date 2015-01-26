#include "../../../lib/parser/tokens.h"
#include "../../../lib/interpreter/pool.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/native/boolean_methods.h"
#include "../../../lib/native/object_methods.h"
#include "../lib/spec.h"

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

char *test_empty_object_truthiness() {
  spec_describe("empty object truthiness");

  FxI_Pool *pool = setup_test_boolean_pool();
  FxN_Object *false_object = fxi_literal_get(pool, "false");

  FxN_Object *object = FxN_Object_create(pool, NULL);

  assert_equal(false_object, fxn_object_is_truthy(object), "is false");

  return NULL;
}

char *test_non_empty_object_truthiness() {
  spec_describe("non-empty object truthiness");

  FxI_Pool *pool = setup_test_boolean_pool();
  FxN_Object *true_object = fxi_literal_get(pool, "true");

  FxN_Object *object = FxN_Object_create(pool, NULL);
  fxn_object_set_attribute(object, "flag", true_object);

  assert_equal(true_object, fxn_object_is_truthy(object), "is true");

  return NULL;
}

char *all_specs() {
  spec_setup("Base Type: Boolean methods");

  run_spec(test_empty_object_truthiness);
  run_spec(test_non_empty_object_truthiness);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);

