#include "object.h"

#include "../bricks/helpers.h"

FxI_Object *FxI_Object_create(FxI_Interpreter *interpreter, FxI_Object *klass) {
  FxI_Object *object = fx_alloc(FxI_Object);
  verify_memory(object);

  FxB_HashMap *attributes = FxB_HashMap_create(FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE);
  verify(attributes);

  fxi_object_class(object) = klass;
  fxi_object_attributes(object) = attributes;

  return object;
error:
  if (object) { fx_pfree(object); }
  return NULL;
}

FxI_Object *fxi_object_set(FxI_Object *self, char *key, FxI_Object *value) {
  fxi_object_set_attribute(self, key, value);
  return value;
error:
  return NULL;
}
