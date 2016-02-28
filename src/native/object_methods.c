#include "object_methods.h"
#include "boolean_methods.h"
#include "../interpreter/interpreter.h"

FxI_Object *fxi_object_is_empty(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments) {
  return fxi_boolean(interpreter, !(fxi_object_attributes_length(self) == 0));
}
