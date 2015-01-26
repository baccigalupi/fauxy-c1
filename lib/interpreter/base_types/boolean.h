#ifndef FxN_Boolean_h
#define FxN_Boolean_h 1

#include "../../parser/expressions.h"
#include "../object.h"
#include "../pool.h"

#define fxn_boolean__value(O)               (fxn_object_get_attribute(O, "value"))
#define fxn_boolean_expression_value(O)     (fxp_literal_bit(fxn_boolean__value(O)))
#define fxn_boolean_value(O)                (((fxn_boolean_expression_value(O))->type) == TOKEN_TRUE ? 1 : 0)

FxN_Object *FxN_Boolean_create(FxI_Pool *pool, FxP_Literal *value);
//FxN_Object *fxn_boolean_is_true(FxN_Object *self);
//FxN_Object *fxn_boolean_is_false(FxN_Object *self);
/*FxN_Object *FxN_Boolean_not(FxN_Object *boolean);*/
/*FxN_Object *FxN_Boolean_to_string(FxN_Object *boolean);*/
/*FxN_Object *FxN_Boolean_to_json();*/


#endif

