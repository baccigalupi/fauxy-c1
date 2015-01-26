#include "../../../../lib/parser/tokens.h"
#include "../../../../lib/interpreter/pool.h"
#include "../../../../lib/interpreter/object.h"
#include "../../../../lib/interpreter/base_types/boolean.h"
#include "../../lib/spec.h"

char *all_specs() {
  spec_setup("Base Type: Boolean methods");

  /*run_spec(setup_test_boolean_pool);*/

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);



