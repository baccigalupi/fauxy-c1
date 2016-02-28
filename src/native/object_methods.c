#include "object_methods.h"
#include "boolean_methods.h"

FxI_Object *fxi_object_is_empty(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments) {
  FxI_Object *boolean;
  if (fxi_object_attributes_length(self) == 0) {
    boolean = fxi_false(interpreter);
  } else {
    boolean = fxi_true(interpreter);
  }

  return boolean;
}
