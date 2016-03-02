#ifndef FxI_Object_Methods_h
#define FxI_Object_Methods_h 1

#include "../interpreter/object.h"
#include "../interpreter/interpreter.h"

FxI_Object *fxi_object_is_empty(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments);

#endif
