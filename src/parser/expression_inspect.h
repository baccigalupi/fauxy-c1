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
json_t *fxp_native_body(              FxP_Expression *expression);

#endif
