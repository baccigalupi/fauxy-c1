#include "method_call_arguments.h"
#include "object.h"
#include "expression_eval.h"
#include <math.h>

FxI_MethodCallArguments *FxI_MethodCallArguments_create(FxI_Interpreter *interpreter, FxP_Expression *list) {
  FxI_Object *object = FxI_Object_create(interpreter, NULL); // TODO: add right class type here

  int length = fxp_list_length(list);
  int i = 0;
  int key_length = log10((double)length) + 2;
  CHAR key[key_length];
  FxP_Expression *arg_expression;
  FxI_Object *arg;

  verify(object);

  for(i = 0; i < length; i++) {
    arg_expression = fxp_list_get(list, i);
    arg = fxi_evaluate(interpreter, arg_expression);
    sprintf(key, "%d", i);
    fxi_object_set_attribute(object, key, arg);
  }

  return object;
error:
  return NULL;
}
