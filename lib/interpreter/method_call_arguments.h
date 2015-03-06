#ifndef __method_call_arguments_h
#define __method_call_arguments_h

#include "structs.h"
#include "../parser/_parser.h"

#define fxi_method_call_arguments_arity(A)    (fxp_list_length(fxn_object_value(A)))

FxI_MethodCallArguments *FxN_MethodCallArguments_create(FxI_Interpreter *interpreter, FxP_List *expression);

#endif
