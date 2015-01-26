#include "../../../lib/interpreter/interpreter.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/interpreter/base_types/boolean.h"
#include "../../../lib/parser/expressions.h"
#include "../lib/spec.h"


char *test_interpeter_setup_objects() {
  spec_describe("setup of interpreter with base objects");

  FxI_Interpreter *interpreter = FxI_Interpreter_create(1, 1, 1);
  fxi_interpreter_setup(interpreter);

  FxN_Object *true_object = fxi_interpreter_get_literal(interpreter, "true");
  FxN_Object *false_object = fxi_interpreter_get_literal(interpreter, "false");

  assert_truthy(fxn_boolean_value(true_object) == true, "true object has value of true");
  assert_truthy(fxn_boolean_value(false_object) == false, "false object has value of false");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *all_specs() {
  spec_setup("Interpreter");

  run_spec(test_interpeter_setup_objects);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);


