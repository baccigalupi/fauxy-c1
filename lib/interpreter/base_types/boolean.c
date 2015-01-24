#include "boolean.h"

FxN_Object *FxN_Boolean_create(FxI_Pool *pool, FxP_Literal *value) {
  FxN_Object *self = FxN_Object_create(pool, NULL); // TODO: switch to boolean class when there is one
  verify(self);

  FxB_String *key = FxB_String_create("value");
  fxn_object_set_attribute(self, key, value);

  return self;
error:
  return NULL;
}
