#include "boolean.h"
#include "../interpreter/pool.h"

FxN_Object *FxN_Boolean_create(FxI_Pool *pool, FxP_Literal *value) {
  FxN_Object *self = FxN_Object_create(pool, NULL); // TODO: switch to boolean class when there is one
  verify(self);

  fxn_object_set_attribute(self, FXN_VALUE_KEY, value);

  return self;
error:
  return NULL;
}

FxN_Object *fxn_boolean_is_truthy(FxN_Object *self) {
  return self;
}

FxN_Object *fxn_boolean_not(FxN_Object *self) {
  FxI_Pool *pool = fxn_object_pool(self);
  FxN_Object *not_value;

  if (fxn_boolean_value(self)) {
    not_value = fxi_literal_get(pool, "false");
  } else {
    not_value = fxi_literal_get(pool, "true");
  }

  return not_value;
}