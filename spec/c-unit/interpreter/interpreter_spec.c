#include "helpers.h"

char *test_interpet_literal_true() {
  spec_describe("'true' returns true object");
  setup_interpreter();

  FxP_Literal *literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_truthy(fxn_boolean_value(object) == true,  "returned object is true");
  // assert that object has the right class

  FxI_Pool *pool = fxi_interpreter_pool(interpreter);
  FxN_Object *stored_object = fxi_literal_get(pool, TRUE_KEY);
  assert_truthy(fxn_boolean_value(object) == true, "literal is set in the pool");

  assert_equal(object, stored_object, "literal returned is same as one stored in the pool");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_false() {
  spec_describe("'false' returns false object");
  setup_interpreter();

  FxP_Literal *literal = FxP_Literal_create(NULL, TOKEN_FALSE);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_truthy(fxn_boolean_value(object) == false,  "returned object is false");
  // assert that object has the right class

  FxI_Pool *pool = fxi_interpreter_pool(interpreter);
  FxN_Object *stored_object = fxi_literal_get(pool, FALSE_KEY);
  assert_truthy(fxn_boolean_value(object) == false, "literal is set in the pool");

  assert_equal(object, stored_object, "literal returned is same as one stored in the pool");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_nil() {
  spec_describe("'nil' returns nil object");
  setup_interpreter();

  FxP_Literal *literal = FxP_Literal_create(NULL, TOKEN_NIL);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_truthy(fxn_object_is_nil(object),  "returned object is nil");
  // assert that object has the right class

  FxI_Pool *pool = fxi_interpreter_pool(interpreter);
  FxN_Object *stored_object = fxi_literal_get(pool, NIL_KEY);
  assert_truthy(fxn_object_is_nil(object), "literal is set in the pool");

  assert_equal(object, stored_object, "literal returned is same as one stored in the pool");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_integer() {
  spec_describe("integer expressions return an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_integer_create("12");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_INTEGER);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_equal(fxi_object_value_short(object), (short)12, "returned the right number");
  // assert that object has the right class

  FxI_Pool *pool = fxi_interpreter_pool(interpreter);
  FxN_Object *stored_object = fxi_literal_get(pool, fxi_literal_key(literal));
  assert_equal(object, stored_object, "literal returned is same as one stored in the pool");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_decimal() {
  spec_describe("decimal literal expression returns an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_decimal_create("1.2");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_FLOAT);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_equal(fxi_object_value_double(object), (double)1.2, "returned the right number");
  // assert that object has the right class

  FxI_Pool *pool = fxi_interpreter_pool(interpreter);
  assert_ints_equal(fxb_hash_map_length(fxi_pool_literals(pool)), 3, "decimal was not added to the pool");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_string() {
  spec_describe("string literal expression returns an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_string_create("hello world");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_FLOAT);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_strings_equal(fxb_string_value(fxi_object_value_string(object)), "hello world", "returned the right string");
  // assert that object has the right class

  FxI_Pool *pool = fxi_interpreter_pool(interpreter);
  FxN_Object *stored_object = fxi_literal_get(pool, fxi_literal_key(literal));
  assert_equal(object, stored_object, "literal returned is same as one stored in the pool");

  fxi_interpreter_free(interpreter);

  return NULL;
}


char *all_specs() {
  spec_setup("Interpreter");

  run_spec(test_interpet_literal_true);
  run_spec(test_interpet_literal_false);
  run_spec(test_interpet_literal_nil);
  run_spec(test_interpet_literal_integer);
  run_spec(test_interpet_literal_decimal);
  run_spec(test_interpet_literal_string);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
