#include "../interpreter/interpreter.h"
#include "../interpreter/class.h"
#include "integer_methods.h"
#include "boolean_methods.h"

// native('fxi_integer_plus')
FxI_Object *fxi_integer_plus(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments) {
  // get first argument
  // extract value from argument
  //
  // short arg_int = fxi_object_value_short(arg);
  short receiver_int = fxi_object_value_short(self);
  // short result = receiver_int + arg_int;
  // put added value into new object
  FxI_Class *klass = fxi_lookup(interpreter, "Integer");
  FxI_Object *object = FxI_Object_create(interpreter, klass);
  /*fxi_object__value(object) = result;*/

  return object;
}
