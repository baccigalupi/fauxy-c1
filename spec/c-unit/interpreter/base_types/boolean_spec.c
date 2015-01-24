#include "../../../../lib/parser/tokens.h"
#include "../../../../lib/interpreter/pool.h"
#include "../../../../lib/interpreter/object.h"
#include "../../../../lib/interpreter/base_types/boolean.h"
#include "../../lib/spec.h"


char *test_is_true_for_false_boolean() {
  spec_describe("false is true?");

  FxI_Pool *pool = FxI_Pool_create(1, 1, 1);
  FxN_Object *false_object = FxN_Boolean_create(pool, false);


  return NULL;
}

char *all_specs() {
  spec_setup("Base Type: Boolean methods");

  run_spec(test_is_true_for_false_boolean);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);



