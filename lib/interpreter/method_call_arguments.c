#include "method_call_arguments.h"
#include "object.h"

FxI_MethodCallArguments *FxN_MethodCallArguments_create(FxI_Interpreter *interpreter, FxP_List *expression) {
  FxN_Object *object = FxN_Object_create(interpreter, NULL); // TODO: add right class type here
  verify(object);
  fxn_object__value(object) = expression;
  return object;
error:
  return NULL;
}
