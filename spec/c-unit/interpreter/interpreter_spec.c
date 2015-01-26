#include "../../../lib/interpreter/interpreter.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/parser/expressions.h"
#include "../../../lib/parser/expression_inspect.h"
#include "../lib/spec.h"


char *test_interpeter_setup_objects() {
  spec_describe("setup of interpreter with base objects");

  FxI_Interpreter *interpreter = FxI_Interpreter_create(1, 1, 1);
  fxi_interpreter_setup(interpreter);

  FxN_Object *true_object = fxi_interpreter_get_literal(interpreter, "true");
  FxN_Object *false_object = fxi_interpreter_get_literal(interpreter, "false");

  FxP_Literal *true_literal = fxn_object_get_attribute(true_object, FXN_BIT_VALUE_KEY);
  assert_truthy(fxp_literal_type(true_literal) == TOKEN_TRUE, "extracted true value is true");

  FxP_Literal *false_literal = fxn_object_get_attribute(false_object, FXN_BIT_VALUE_KEY);
  assert_truthy(fxp_literal_type(false_literal) == TOKEN_FALSE, "extracted true value is true");

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


