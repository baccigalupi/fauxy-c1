#include "../../../lib/interpreter/object.h"
#include "../../../lib/bricks/hash_map.h"
#include "../lib/spec.h"

char *find_or_create_in_pool() {
  spec_describe("find or create in pool");
  FxI_Pool *pool = FxI_Pool_create(1, 1, 1);

  FxN_Class *klass = fxi_class_find_or_create(pool, "MyClass", NULL);
  assert_strings_equal(fxn_class_name(klass), "MyClass", "returns class with right name when new");

  assert_equal(klass, fxi_class_find_or_create(pool, "MyClass", NULL), "returns same class when already exists");

  return NULL;
}

char *set_method_with_no_name_match() {
  spec_describe("set method with no group yet created");

  FxN_Class *klass = FxN_Class_create("MyClass", NULL);
  FxN_Function *function = fx_alloc(FxN_Function);
  fxn_class_set_method(klass, "my-call", function);

  assert_ints_equal(fxn_class_method_count(klass), 1, "has the right number of methods");

  return NULL;
}

char *all_specs() {
  spec_setup("Class");

  run_spec(find_or_create_in_pool);
  run_spec(set_method_with_no_name_match);
  /*run_spec(set_method_with_name_match);*/

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);


