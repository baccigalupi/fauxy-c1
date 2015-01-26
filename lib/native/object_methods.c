#include "object_methods.h"

FxN_Object *fxn_object_is_truthy(FxN_Object *self) {
  FxI_Pool *pool = fxn_object_pool(self);

  FxN_Object *boolean;
  if ( fxn_object_attributes_length(self) == 0) {
    boolean = fxi_literal_get(pool, "false");
  } else {
    boolean = fxi_literal_get(pool, "true");
  }

  return boolean;
}

