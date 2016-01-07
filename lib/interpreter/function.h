#ifndef FxI_Function_h
#define FxI_Function_h 1

#include "structs.h"

FxI_FunctionDefinition *FxI_Function_create(char *name, FxI_Object *super_class);
// arity
// arguments_match // given argument values, does it match
// arguments_signature_match // is this a duplicate method because the signature is identical

#endif
