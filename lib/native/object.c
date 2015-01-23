#include "object.h"

#include "../bricks/helpers.h"

FxN_Object *FxN_Object_create(FxN_Class *scope) {
  FxN_Object *object = fx_alloc(FxN_Object);
  verify_memory(object);

  FxB_HashMap *attributes = FxB_HashMap_create(50);
  verify(attributes);

  fxn_object_scope(object) = scope;
  fxn_object_attributes(object) = attributes;

  return object;
error:
  if (object) { fx_pfree(object); }
  return NULL;
}

FxN_Object *fxn_object_get_attribute(FxN_Object *self, FxB_String *key) {
  return fxn_object_mapped_attr_get(self, key);
}

void fxn_object_set_attribute(FxN_Object *self, FxB_String *key, FxN_Object *value) {
  fxn_object_mapped_attr_set(self, key, value);
}


