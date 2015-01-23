#include "../../../lib/interpreter/object.h"
#include "../../../lib/bricks/string.h"
#include "../lib/spec.h"


char *test_set_and_get_attribute() {
  spec_describe("setting and getting attributes of objects");

  FxI_Pool   *pool =    FxI_Pool_create(1, 1, 1);
  FxN_Object *object =  FxN_Object_create(pool, NULL);
  FxN_Object *value =   FxN_Object_create(pool, NULL);
  FxB_String *key =     FxB_String_create("thing");

  fxn_object_set_attribute(object, key, value);
  FxN_Object *gotten = fxn_object_get_attribute(object, key);

  assert_equal(gotten, value, "stored attribute is save as attribute gotten by same key");

  string_free(key);
  fxn_object_free(object);
  fxn_object_free(value);
  fxi_pool_free(pool);

  return NULL;
}

char *all_specs() {
  spec_setup("Native Object");

  run_spec(test_set_and_get_attribute);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);

