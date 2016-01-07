#include "helpers.h"

char *test_set_and_get_attribute() {
  spec_describe("setting and getting attributes of objects");

  setup_interpreter();

  FxI_Object *object =  FxI_Object_create(interpreter, NULL);
  FxI_Object *value =   FxI_Object_create(interpreter, NULL);
  char *key = "thing";

  fxn_object_set_attribute(object, key, value);
  FxI_Object *gotten = fxn_object_get_attribute(object, key);

  assert_equal(gotten, value, "stored attribute is save as attribute gotten by same key");

  fxn_object_free(object);
  fxn_object_free(value);
  fxi_interpreter_free(interpreter);

  return NULL;
}

char *all_specs() {
  spec_setup("Native Object");

  run_spec(test_set_and_get_attribute);

  spec_teardown();

  return NULL;
}

run_all_specs(all_specs);
