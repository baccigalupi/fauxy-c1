#ifndef __method_call_arguments_h
#define __method_call_arguments_h

#include "structs.h"
#include "../parser/_parser.h"

#define fxi_method_call_arguments_arity(A)    (fxp_list_length(fxi_object_value(A)))

FxI_MethodCallArguments *FxI_MethodCallArguments_create(FxI_Interpreter *interpreter, FxP_Expression *list);

#endif
