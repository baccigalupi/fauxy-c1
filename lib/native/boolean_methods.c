#include "boolean_methods.h"
#include "../interpreter/pool.h"

FxI_Object *FxI_Boolean_create(FxI_Interpreter *interpreter, FxP_Literal *value) {
  FxI_Object *self = FxI_Object_create(interpreter, NULL); // TODO: switch to boolean class when there is one
  verify(self);

  fxn_object__value(self) = value;

  return self;
error:
  return NULL;
}

FxI_Object *fxn_boolean_not(FxI_Object *self) {
  FxI_Interpreter *interpreter = fxn_object_interpreter(self);
  FxI_Object *not_value;

  if (fxn_boolean_value(self)) {
    not_value = fxi_literal_get(interpreter, FALSE_KEY);
  } else {
    not_value = fxi_literal_get(interpreter, TRUE_KEY);
  }

  return not_value;
}
