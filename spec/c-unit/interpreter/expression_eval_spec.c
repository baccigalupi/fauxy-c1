#include "helpers.h"

char *test_class_objects_exist_in_global() {
  spec_describe("essential classes are set in the global space");
  setup_interpreter();

  FxI_Object *return_value = NULL;
  FxI_Class *klass = NULL;
  FxI_Class *object_class = NULL;

  klass = fxi_lookup(interpreter, "Class");
  assert_truthy(klass, "Class exists");
  assert_equal(fxi_class_super_class(klass), NULL, "Class has no superclass");

  object_class = fxi_lookup(interpreter, "Object");
  assert_truthy(object_class, "Object exists");
  assert_equal(fxi_class_super_class(object_class), klass, "Object superclass is class");

  return_value = fxi_lookup(interpreter, "Function");
  assert_truthy(return_value, "Function exists");
  assert_equal(fxi_class_super_class(return_value), object_class, "Function superclass is Object");

  return_value = fxi_lookup(interpreter, "Arguments");
  assert_truthy(return_value, "Arguments exists");
  assert_equal(fxi_class_super_class(return_value), object_class, "Arguments superclass is Object");

  return_value = fxi_lookup(interpreter, "Boolean");
  assert_truthy(return_value, "Boolean exists");
  assert_equal(fxi_class_super_class(return_value), object_class, "Boolean superclass is Object");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_true() {
  spec_describe("literal evaluation: 'true' returns true object");
  setup_interpreter();

  FxP_Bit *bit =         FxP_Bit_string_create("true");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_TRUE);
  FxI_Object *object =   fxi_evaluate(interpreter, literal);

  assert_truthy(fxi_boolean_value(object) == true,  "returned object is true");
  assert_equal(fxi_object_class(object), fxi_lookup(interpreter, "Boolean"), "is a Boolean");

  FxI_Object *global_object = fxi_true(interpreter);
  assert_equal(object, global_object, "literal returned is same as one stored in the global context");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_false() {
  spec_describe("literal evaluation: 'false' returns false object");
  setup_interpreter();

  FxP_Bit *bit =         FxP_Bit_string_create("false");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_FALSE);
  FxI_Object *object =   fxi_evaluate(interpreter, literal);

  assert_truthy(fxi_boolean_value(object) == false,  "returned object is false");
  assert_equal(fxi_object_class(object), fxi_lookup(interpreter, "Boolean"), "is a Boolean");

  FxI_Object *global_object = fxi_false(interpreter);
  assert_equal(object, global_object, "literal returned is same as one stored in the global context");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_integer() {
  spec_describe("literal evaluation: integer literal return an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_integer_create("12");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_INTEGER);
  FxI_Object *object = fxi_evaluate(interpreter, literal);

  assert_equal(fxi_object_value_short(object), (short)12, "returned the right number");
  assert_equal(fxi_object_class(object), fxi_lookup(interpreter, "Integer"), "is a Integer");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_decimal() {
  spec_describe("literal evaluation: decimal literal returns an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_decimal_create("1.2");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_FLOAT);
  FxI_Object *object = fxi_evaluate(interpreter, literal);

  assert_equal(fxi_object_value_double(object), (double)1.2, "returned the right number");
  assert_equal(fxi_object_class(object), fxi_lookup(interpreter, "Decimal"), "is a Decimal");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_interpet_literal_string() {
  spec_describe("literal evaluation: string literal returns an object");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_string_create("hello world");
  FxP_Literal *literal = FxP_Literal_create(bit, TOKEN_STRING);
  FxI_Object *object = fxi_evaluate(interpreter, literal);

  assert_strings_equal(fxi_object_string_value(object), "hello world", "returned the right string");
  assert_equal(fxi_object_class(object), fxi_lookup(interpreter, "String"), "is a String");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_global_assigned_lookup() {
  spec_describe("test lookup of global");
  setup_interpreter();

  FxP_Bit     *value_bit =      FxP_Bit_string_create("Hello Fauxy world!");
  FxP_Literal *value =          FxP_Literal_create(value_bit, TOKEN_STRING);

  FxI_Object  *value_object =   fxi_evaluate(interpreter, value);

  FxP_Bit     *lookup_bit =     FxP_Bit_string_create("greeting");
  FxP_Lookup  *lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);

  FxP_Expression *assignment =  FxP_ColonExpression_create(lookup, value);

  FxI_Object   *value_dup =     fxi_evaluate(interpreter, assignment);

  assert_strings_equal(
    fxi_object_string_value(value_dup),
    fxi_object_string_value(value_object),
    "evaluation of assignment returns what is assigned to it"
  );

  FxI_Object *evaluation = fxi_evaluate(interpreter, lookup);
  assert_equal(
    fxi_object_string_value(evaluation),
    fxi_object_string_value(value_object),
    "lookup of the id returns the object with the same value as the original literal"
  );

  return NULL;
}

char *test_context_lookup_of_literal() {
  spec_describe("test lookup of attribute in local context");
  setup_interpreter();

  FxI_Object *object = FxI_Object_create(interpreter, NULL);
  fxi_interpreter_push_context(interpreter, object);

  FxP_Bit     *value_bit =      FxP_Bit_string_create("Hello Fauxy world!");
  FxP_Literal *value =          FxP_Literal_create(value_bit, TOKEN_STRING);

  FxI_Object  *value_object =   fxi_evaluate(interpreter, value);

  FxP_Bit     *lookup_bit =     FxP_Bit_string_create("greeting");
  FxP_Lookup  *lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);

  FxP_Expression *assignment =  FxP_ColonExpression_create(lookup, value);

  FxI_Object   *assign_return_value = fxi_evaluate(interpreter, assignment);

  assert_strings_equal(
    fxi_object_string_value(assign_return_value),
    fxi_object_string_value(value_object),
    "evaluation of assignment returns what is assigned to it"
  );

  FxI_Object *attr = fxi_object_get_attribute(object, "greeting");
  assert_strings_equal(
    fxi_object_string_value(attr),
    fxi_object_string_value(value_object),
    "literal is stored in context"
  );

  FxI_Object *evaluation = fxi_evaluate(interpreter, lookup);
  assert_equal(
    fxi_object_string_value(evaluation),
    fxi_object_string_value(value_object),
    "lookup of the id returns the object with the same value as the original literal"
  );

  return NULL;
}

char *test_context_lookup_of_global() {
  spec_describe("test lookup of global from local context");
  setup_interpreter();

  FxI_Object *object = FxI_Object_create(interpreter, NULL);

  FxP_Bit     *value_bit =      FxP_Bit_string_create("Hello Fauxy world!");
  FxP_Literal *value =          FxP_Literal_create(value_bit, TOKEN_STRING);

  FxI_Object  *value_object =   fxi_evaluate(interpreter, value);

  FxP_Bit     *lookup_bit =     FxP_Bit_string_create("greeting");
  FxP_Lookup  *lookup =         FxP_Lookup_create(lookup_bit, TOKEN_ID);

  FxP_Expression *assignment =  FxP_ColonExpression_create(lookup, value);

  FxI_Object   *assign_return_value = fxi_evaluate(interpreter, assignment);

  fxi_interpreter_push_context(interpreter, object);

  FxI_Object *evaluation = fxi_evaluate(interpreter, lookup);
  assert_equal(
    fxi_object_string_value(evaluation),
    fxi_object_string_value(value_object),
    "lookup of the id works in a context higher than current"
  );

  return NULL;
}

char *test_function_declaration() {
  spec_describe("function definition evaluation: returns function definition");
  setup_interpreter();

  FxP_Literal *literal = FxP_Literal_create(NULL, TOKEN_TRUE);

  // expressions
  FxP_Expressions *expressions = FxP_Expressions_create();
  fxp_expression_push(expressions, literal);
  // function definition setup
  FxP_FunctionDefinition *function_definition = FxP_FunctionDefinition_create_no_args();
  fxp_function_definition_set_expressions(function_definition, expressions);

  FxI_Object *evaluation = fxi_evaluate(interpreter, function_definition);
  assert_equal(fxi_object_value(evaluation), function_definition, "returns an object with the expression stored in the value");
  // TODO: assert about the class/type

  return NULL;
}

char *test_assignment_to_global() {
  spec_describe("assignment to global space");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_string_create("whatever");
  FxP_Lookup *lookup = FxP_Lookup_create(bit, TOKEN_ID);
  FxP_Bit *true_bit =         FxP_Bit_string_create("true");
  FxP_Literal *true_literal = FxP_Literal_create(true_bit, TOKEN_TRUE);

  FxP_ColonExpression *assignment = FxP_ColonExpression_create(lookup, true_literal);

  // set the variable in the interpreter context
  FxI_Object *object = fxi_evaluate(interpreter, assignment);
  assert_equal(fxi_boolean_value(object), true, "expression returns assigned value");

  // evaluate the lookup to get the value ... easier
  object = fxi_evaluate(interpreter, lookup);
  assert_equal(fxi_boolean_value(object), true, "lookup retrieves the assigned value");

  return NULL;
}

char *test_expressions_evaluation() {
  spec_describe("evaluation of expressions");
  setup_interpreter();

  FxP_Bit *bit = FxP_Bit_string_create("what-do-you-think?");
  FxP_Lookup *lookup = FxP_Lookup_create(bit, TOKEN_ID);
  FxP_Bit *true_bit =         FxP_Bit_string_create("true");
  FxP_Literal *true_literal = FxP_Literal_create(true_bit, TOKEN_TRUE);
  FxP_ColonExpression *assignment = FxP_ColonExpression_create(lookup, true_literal);

  FxP_Bit *false_bit =         FxP_Bit_string_create("false");
  FxP_Literal *false_literal = FxP_Literal_create(false_bit, TOKEN_FALSE);

  FxP_Expressions *expressions = FxP_Expressions_create();
  fxp_expression_push(expressions, assignment);
  fxp_expression_push(expressions, false_literal);

  FxI_Object *object = fxi_evaluate(interpreter, expressions);
  assert_equal(fxi_boolean_value(object), false, "returns value of last expression");

  // evaluate the lookup to get the value ... easier
  object = fxi_evaluate(interpreter, lookup);
  assert_equal(fxi_boolean_value(object), true, "evaluates earlier expressions");

  return NULL;
}

char *test_import_expression_on_global_space() {
  spec_describe("import expression adds to global namespace");
  setup_interpreter();

  // currently path is from root run location, not relative to here or file require
  FxP_Bit *bit                              = FxP_Bit_string_create("spec/c-unit/interpreter/fixtures/import-test.fx");
  FxP_Literal *literal                      = FxP_Literal_create(bit, TOKEN_STRING);
  FxP_ImportExpression *import_expression   = FxP_ImportExpression_create(literal);

  FxI_Object *object = fxi_evaluate(interpreter, import_expression);
  assert_equal(fxi_boolean_value(object), true, "returns the last expression return value from the import");

  bit = FxP_Bit_string_create("it-worked?");
  FxP_Lookup *lookup = FxP_Lookup_create(bit, TOKEN_ID);
  object = fxi_evaluate(interpreter, lookup);

  // this is segfaulting because the object is not found via lookup
  assert_equal(fxi_boolean_value(object), true, "import code run against current interpreter context");

  return NULL;
}

char *test_native() {
  // native('fxi_boolean_not');
  spec_describe("native returns a method object");
  setup_interpreter();

  FxI_NativeRegistry_add(fxi_interpreter_registry(interpreter), "fxi_boolean_not", &fxi_boolean_not);

  FxP_Bit *bit                              = FxP_Bit_string_create("fxi_boolean_not");
  FxP_Literal *literal                      = FxP_Literal_create(bit, TOKEN_STRING);
  FxP_NativeExpression *native_expression   = FxP_NativeExpression_create_no_args(literal);

  FxI_Object *object = fxi_evaluate(interpreter, native_expression);

  assert_equal(fxi_object__value(object), &fxi_boolean_not, "stores address of function in the private value of the object");

  return NULL;
}

char *all_specs() {
  spec_setup("Interpreter");

  run_spec(test_class_objects_exist_in_global);

  run_spec(test_interpet_literal_true);
  run_spec(test_interpet_literal_false);
  run_spec(test_interpet_literal_integer);
  run_spec(test_interpet_literal_decimal);
  run_spec(test_interpet_literal_string);

  run_spec(test_global_assigned_lookup);
  run_spec(test_context_lookup_of_literal);
  run_spec(test_context_lookup_of_global);

  run_spec(test_assignment_to_global);

  run_spec(test_expressions_evaluation);

  run_spec(test_function_declaration);

  run_spec(test_import_expression_on_global_space);
  run_spec(test_native);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
