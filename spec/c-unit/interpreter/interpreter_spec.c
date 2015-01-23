#include "../../../lib/interpreter/interpreter.h"
#include "../lib/spec.h"


char *test_interpeter_setup() {
  spec_describe("setup of interpreter with base objects and classes");

  FxI_Interpreter *interpreter = FxI_Interpreter_create(1, 1, 1);
  fxi_interpreter_setup(interpreter);

  fxi_interpreter_free(interpreter);
  return NULL;
}

char *all_specs() {
  spec_setup("Interpreter");

  run_spec(test_interpeter_setup);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);


