#ifndef __FxP_Expression_inspect
#define __FxP_Expression_inspect 1

#include "../bricks/string.h"
#include "expressions.h"

void   *fxp_inspect(void *element); // void * for use in array iterators

FxB_String *fxp_literal_body_inspect(     FxP_Expression *expression);
FxB_String *fxp_lookup_body_inspect(      FxP_Expression *expression);
FxB_String *fxp_collection_body_inspect(  FxP_Expression *expression);
FxB_String *fxp_list_body_inspect(        FxP_Expression *expression);
FxB_String *fxp_method_call_body_inspect(      FxP_Expression *expression);
FxB_String *fxp_function_definition_body_inspect(    FxP_Expression *expression);
FxB_String *fxp_left_right_inspect(       FxP_Expression *expression);
FxB_String *fxp_colon_exp_inspect(        FxP_Expression *expression);

FxB_String *fxp_expression_join(FxP_Expression *expression, FxB_String *value);
FxB_String *fxp_expression_type_description(FxP_Expression *expression);
FxB_String *fxp_literal_class_description(FxP_Literal *literal);
FxB_String *fxp_lookup_type_description(FxP_Lookup *literal);
FxB_String *fxp_import_expression_body_inspect(FxP_Expression *expression);

#endif
