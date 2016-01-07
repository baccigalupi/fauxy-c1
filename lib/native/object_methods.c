#include "object_methods.h"
#include "boolean_methods.h"

FxI_Object *fxn_object_is_empty(FxI_Object *self) {
  FxI_Interpreter *interpreter = fxn_object_interpreter(self);

  FxI_Object *boolean;
  if ( fxn_object_attributes_length(self) == 0) {
    boolean = fxi_literal_get(interpreter, FALSE_KEY);
  } else {
    boolean = fxi_literal_get(interpreter, TRUE_KEY);
  }

  return boolean;
}
