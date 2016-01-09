#include "boolean_methods.h"
#include "../interpreter/pool.h"

FxI_Object *FxI_Boolean_create(FxI_Interpreter *interpreter, FxP_Literal *value) {
  FxI_Object *self = FxI_Object_create(interpreter, NULL); // TODO: switch to boolean class when there is one
  verify(self);

  fxi_object__value(self) = value;

  return self;
error:
  return NULL;
}

// native(:fxi_boolean_not)
FxI_Object *fxi_boolean_not(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments) {
  FxI_Object *not_value;

  if (fxi_boolean_value(self)) {
    not_value = fxi_literal_get(interpreter, FALSE_KEY);
  } else {
    not_value = fxi_literal_get(interpreter, TRUE_KEY);
  }

  return not_value;
}
