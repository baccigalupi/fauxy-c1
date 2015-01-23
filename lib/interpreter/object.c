#include "object.h"

#include "../bricks/helpers.h"

FxN_Object *FxN_Object_create(FxN_Class *scope) {
  FxN_Object *object = fx_alloc(FxN_Object);
  verify_memory(object);

  FxB_HashMap *attributes = FxB_HashMap_create(FXN_OBJECT_ATTRIBUTE_HASHMAP_SIZE);
  verify(attributes);

  fxn_object_scope(object) = scope;
  fxn_object_attributes(object) = attributes;

  return object;
error:
  if (object) { fx_pfree(object); }
  return NULL;
}

