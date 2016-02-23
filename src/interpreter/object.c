#include "object.h"

#include "../bricks/helpers.h"

FxI_Object *FxI_Object_create(FxI_Interpreter *interpreter, FxI_Object *scope) {
  FxI_Object *object = fx_alloc(FxI_Object);
  verify_memory(object);

  fxi_object_type(object) = FX_OBJECT;

  FxB_HashMap *attributes = FxB_HashMap_create(FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE);
  verify(attributes);

  fxi_object_scope(object) = scope;
  fxi_object_attributes(object) = attributes;

  return object;
error:
  if (object) { fx_pfree(object); }
  return NULL;
}

FxI_Object *fxi_object_set(FxI_Object *self, char *key, FxI_Object *value) {
  verify(fxi_object_is_open(self))
  fxi_object_set_attribute(self, key, value);
  return value;
error:
  return NULL;
}
