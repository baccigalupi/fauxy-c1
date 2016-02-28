#ifndef FxI_Boolean_h
#define FxI_Boolean_h 1

// these are the token enumerables as strings
#define TRUE_KEY  "258"
#define FALSE_KEY  "259"


#include "../bricks/helpers.h"
#include "../parser/expressions.h"
#include "../interpreter/object.h"
#include "../interpreter/interpreter.h"

#define fxi_boolean_value(O)  (fxp_literal_type(fxi_object_value(O)) == TOKEN_TRUE ? true : false)

FxI_Object *FxI_Boolean_create(FxI_Interpreter *interpreter, FxP_Literal *value);

FxI_Object *fxi_boolean_not(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments);


#endif
