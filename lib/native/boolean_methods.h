#ifndef FxI_Boolean_h
#define FxI_Boolean_h 1

#define TRUE_KEY  "258"
#define FALSE_KEY  "259"

#include "../parser/expressions.h"
#include "../interpreter/object.h"
#include "../interpreter/interpreter.h"

#define fxn_boolean_value(O)                (fxp_literal_type(fxn_object_value(O)) == TOKEN_TRUE ? 1 : 0)

FxI_Object *FxI_Boolean_create(FxI_Interpreter *interpreter, FxP_Literal *value);
FxI_Object *fxn_boolean_is_truthy(FxI_Object *self);
FxI_Object *fxn_boolean_not(FxI_Object *boolean);
/*FxI_String *fxn_boolean_to_json();*/
/*FxI_String *fxn_boolean_to_string(FxI_Object *boolean);*/


#endif
