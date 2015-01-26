#include "boolean.h"

FxN_Object *FxN_Boolean_create(FxI_Pool *pool, FxP_Literal *value) {
  FxN_Object *self = FxN_Object_create(pool, NULL); // TODO: switch to boolean class when there is one
  verify(self);

  fxn_object_set_attribute(self, FXN_VALUE_KEY, value);

  return self;
error:
  return NULL;
}
