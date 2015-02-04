#include "../../../lib/interpreter/interpreter.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/interpreter/expression_eval.h"
#include "../../../lib/native/boolean_methods.h"
#include "../../../lib/native/nil_methods.h"
#include "../../../lib/parser/expressions.h"
#include "../../../lib/parser/expression_inspect.h"
#include "../../../lib/bricks/string.h"
#include "../lib/spec.h"

#define setup_interpreter()   FxI_Interpreter *interpreter = FxI_Interpreter_create(6, 1, 1); \
                              fxi_interpreter_setup(interpreter);


char *test_interpet_literal_true() {
  spec_describe("get true object from interpreter");
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
  spec_describe("get false object from interpreter");
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
  spec_describe("get nil object from interpreter");
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

/*char *test_global_assignment() {*/
  /*spec_describe("global assign");*/
  /*setup_interpreter();*/

  /*char *text = calloc(4, sizeof(char));*/
  /*strcpy(text, "foo");*/
  /*FxP_Bit *left_bit = FxP_Bit_string_create(text);*/
  /*FxP_Lookup *left = FxP_Lookup_create(left_bit, TOKEN_ID);*/

  /*FxP_Literal *right = FxP_Literal_create(NULL, TOKEN_TRUE);*/

  /*FxP_Expression *assignment_expression = FxP_ColonExpression_create(left, right);*/

  /*FxN_Object *expression_result = fxi_evaluate(interpreter, assignment_expression);*/
  /*FxN_Object *foo_result = fxi_interpreter_get(interpreter, "foo");*/
  /*FxN_Object *true_object = fxi_interpreter_get_literal(interpreter, "true");*/

  /*assert_equal(expression_result, true_object, "eval returns right object");*/
  /*assert_equal(foo_result, true_object, "assignment assigns result");*/

  /*return NULL;*/
/*}*/


char *all_specs() {
  spec_setup("Interpreter");

  run_spec(test_interpet_literal_true);
  run_spec(test_interpet_literal_false);
  run_spec(test_interpet_literal_nil);
  /*run_spec(test_literal_creation_interpretation);*/
  /*run_spec(test_global_assignment);*/

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
