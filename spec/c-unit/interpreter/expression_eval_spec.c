#include "helpers.h"

char *test_interpet_literal_true() {
  spec_describe("'true' returns true object");
  setup_interpreter();

  FxP_Literal *literal = FxP_Literal_create(NULL, TOKEN_TRUE);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_truthy(fxn_boolean_value(object) == true,  "returned object is true");
  // assert that object has the right class

  FxN_Object *stored_object = fxi_literal_get(interpreter, TRUE_KEY);
  assert_truthy(fxn_boolean_value(object) == true, "literal is set in the interpreter");

  assert_equal(object, stored_object, "literal returned is same as one stored in the interpreter");

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

  FxN_Object *stored_object = fxi_literal_get(interpreter, FALSE_KEY);
  assert_truthy(fxn_boolean_value(object) == false, "literal is set in the interpreter");

  assert_equal(object, stored_object, "literal returned is same as one stored in the interpreter");

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

  FxN_Object *stored_object = fxi_literal_get(interpreter, NIL_KEY);
  assert_truthy(fxn_object_is_nil(object), "literal is set in the interpreter");

  assert_equal(object, stored_object, "literal returned is same as one stored in the interpreter");

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

  FxN_Object *stored_object = fxi_literal_get(interpreter, fxi_literal_key(literal));
  assert_equal(object, stored_object, "literal returned is same as one stored in the interpreter");

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

  assert_ints_equal(fxi_interpreter_literal_length(interpreter), 3, "decimal was not added to the interpreter");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_string() {
  spec_describe("string literal expression returns an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_string_create("hello world");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);
  FxN_Object *object = fxi_evaluate(interpreter, literal);

  assert_strings_equal(fxb_string_value(fxi_object_value_string(object)), "hello world", "returned the right string");
  // assert that object has the right class

  FxN_Object *stored_object = fxi_literal_get(interpreter, fxi_literal_key(literal));
  assert_equal(object, stored_object, "literal returned is same as one stored in the interpreter");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_global_assignment_of_literal() {
  spec_describe("assigning literal to the global namespace and then retrieving it");
  setup_interpreter();

  FxP_Bit     *value_bit =      FxP_Bit_string_create("Hello Fauxy world!");
  FxP_Literal *value =          FxP_Literal_create(value_bit, TOKEN_STRING);

  FxN_Object  *value_object =   fxi_evaluate(interpreter, value);

  FxP_Bit     *lookup_bit =     FxP_Bit_string_create("greeting");
  FxP_Lookup  *lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);

  FxP_Expression *assignment =  FxP_ColonExpression_create(lookup, value);

  FxN_Object   *value_dup =     fxi_evaluate(interpreter, assignment);

  assert_equal(value_dup, value_object, "evaluation of assignment returns what is assigned to it");
  FxN_Object *evaluation = fxi_evaluate(interpreter, lookup);
  assert_equal(evaluation, value_object, "lookup of the id returns the object");

  return NULL;
}

char *test_context_assignment_of_literal() {
  spec_describe("setting a literal inside the current context (non-global) and then retrieving it");
  setup_interpreter();

  FxN_Object *object = FxN_Object_create(interpreter, NULL);
  fxi_interpreter_push_context(interpreter, object);

  FxP_Bit     *value_bit =      FxP_Bit_string_create("Hello Fauxy world!");
  FxP_Literal *value =          FxP_Literal_create(value_bit, TOKEN_STRING);

  FxN_Object  *value_object =   fxi_evaluate(interpreter, value);

  FxP_Bit     *lookup_bit =     FxP_Bit_string_create("greeting");
  FxP_Lookup  *lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);

  FxP_Expression *assignment =  FxP_ColonExpression_create(lookup, value);

  FxN_Object   *assign_return_value = fxi_evaluate(interpreter, assignment);

  assert_equal(assign_return_value, value_object, "evaluation of assignment returns what is assigned to it");

  FxN_Object *attr = fxn_object_get_attribute(object, "273-greeting");
  assert_equal(attr, value_object, "literal is stored in context");

  FxN_Object *evaluation = fxi_evaluate(interpreter, lookup);
  assert_equal(evaluation, value_object, "lookup of the id in context returns the object");

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

  run_spec(test_global_assignment_of_literal);
  run_spec(test_context_assignment_of_literal);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
