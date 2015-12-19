#ifndef __FxP_Expression_inspect
#define __FxP_Expression_inspect 1

#include "../bricks/string.h"
#include "../bricks/json_gen.h"
#include "expressions.h"

void   *fxp_inspect(void *element); // void * for use in array iterators
json_t *fxp_inspection_body(          FxP_Expression *expression);

json_t *fxp_literal_body(             FxP_Expression *expression);
json_t *fxp_lookup_body(              FxP_Expression *expression);
json_t *fxp_method_call_body(         FxP_Expression *expression);
json_t *fxp_function_definition_body( FxP_Expression *expression);
json_t *fxp_forward_list_body(        FxP_Expression *expression);
json_t *fxp_backwards_list_body(      FxP_Expression *expression);
json_t *fxp_left_right_body(          FxP_Expression *expression);
json_t *fxp_import_body(              FxP_Expression *expression);

FxB_String *fxp_literal_class_description(FxP_Literal *literal);
FxB_String *fxp_lookup_type_description(FxP_Lookup *literal);

#endif
