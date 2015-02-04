#ifndef FxN_Boolean_h
#define FxN_Boolean_h 1

#define TRUE_KEY  "258"
#define FALSE_KEY  "259"

#include "../parser/expressions.h"
#include "../interpreter/object.h"
#include "../interpreter/pool.h"

#define fxn_boolean_value(O)                (fxp_literal_type(fxn_object_value(O)) == TOKEN_TRUE ? 1 : 0)

FxN_Object *FxN_Boolean_create(FxI_Pool *pool, FxP_Literal *value);
FxN_Object *fxn_boolean_is_truthy(FxN_Object *self);
FxN_Object *fxn_boolean_not(FxN_Object *boolean);
/*FxN_String *fxn_boolean_to_json();*/
/*FxN_String *fxn_boolean_to_string(FxN_Object *boolean);*/


#endif
