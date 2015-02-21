#include "nil_methods.h"
#include "boolean_methods.h"

// TODO: this is identical to the boolean, except that eventuall the class context
// will be passed in. Should be a literal create object function that each can call
// or define
FxN_Object *FxN_Nil_create(FxI_Interpreter *interpreter, FxP_Literal *value) {
  FxN_Object *self = FxN_Object_create(interpreter, NULL); // TODO: switch to Nil class
  verify(self);

  fxn_object_value(self) = value;

  return self;
error:
  return NULL;
}

// very similar code to boolean not, except for the conditional
FxN_Object *fxn_object_is_nil(FxN_Object *self) {
  FxI_Interpreter *interpreter = fxn_object_interpreter(self);

  FxN_Object *nil_object = fxi_literal_get(interpreter, NIL_KEY);

  FxN_Object *boolean;
  if ( nil_object == self ) {
    boolean = fxi_literal_get(interpreter, TRUE_KEY);
  } else {
    boolean = fxi_literal_get(interpreter, FALSE_KEY);
  }

  return boolean;
}
