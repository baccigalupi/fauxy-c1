#include "helpers.h"

char *test_literal_setup() {
  setup_interpreter();

  assert_ints_equal(fxi_interpreter_literal_length(interpreter), 2, "has three literals");
  assert_truthy(fxi_literal_get(interpreter, TRUE_KEY), "true has object by key");
  assert_truthy(fxi_literal_get(interpreter, FALSE_KEY), "false has object by key");

  fxi_interpreter_free(interpreter);

  return NULL;
}

char *test_class_setup() {
  setup_interpreter();

  // assert_truthy(fxi_global_get(interpreter, "274-Object"), "has an object by key");
  // assert_truthy(fxi_global_get(interpreter, "274-Boolean"), "false has object by key");

  return NULL;
}


char *all_specs() {
  spec_setup("Interpreter setup");

  run_spec(test_literal_setup);
  // run_spec(test_class_setup);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
