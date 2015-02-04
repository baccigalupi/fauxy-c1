#ifndef FxN_Nil_h
#define FxN_Nil_h 1

#define NIL_KEY "260"

#include "../parser/expressions.h"
#include "../interpreter/object.h"
#include "../interpreter/pool.h"

FxN_Object *FxN_Nil_create(FxI_Pool *pool, FxP_Literal *value);
FxN_Object *fxn_object_is_nil(FxN_Object *self);
/*FxN_String *fxn_nil_to_json();*/
/*FxN_String *fxn_nil_to_string(FxN_Object *boolean);*/

#endif
