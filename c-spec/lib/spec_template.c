// cp c-spec/lib/spec_template.c c-spec/...

// #include "../../lib/my-path.h"

#include "../lib/spec.h"

char *test_something() {
  spec_describe("Testing something important");

  // setup

  // assertions
  assert_ints_equal(1, 1, "ints equal");

  // cleanup

  return NULL;
}

char *all_specs() {
  spec_setup("My Lib");

  run_spec(test_something);
  // and others here

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
