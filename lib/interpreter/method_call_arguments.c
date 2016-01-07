#include "method_call_arguments.h"
#include "object.h"

// This will be important when arguments is available as a local within function declarations,
// not so much right now.
FxI_MethodCallArguments *FxI_MethodCallArguments_create(FxI_Interpreter *interpreter, FxP_List *expression) {
  FxI_Object *object = FxI_Object_create(interpreter, NULL); // TODO: add right class type here
  verify(object);
  fxi_object__value(object) = expression;
  return object;
error:
  return NULL;
}
