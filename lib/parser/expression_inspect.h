#ifndef __FxP_Expression_inspect
#define __FxP_Expression_inspect 1

#include "../bricks/string.h"
#include "expressions.h"

void   *fxp_inspect(void *element); // void * for use in array iterators

String *fxp_literal_body_inspect(     FxP_Expression *expression);
String *fxp_lookup_body_inspect(      FxP_Expression *expression);
String *fxp_collection_body_inspect(  FxP_Expression *expression);
String *fxp_method_body_inspect(      FxP_Expression *expression);
String *fxp_function_body_inspect(    FxP_Expression *expression);
String *fxp_local_assign_body_inspect(FxP_Expression *expression);
// typedef FxP_Expression FxP_ColonExpression;

String *fxp_expression_type_description(FxP_Expression *expression);
String *fxp_literal_class_description(FxP_Literal *literal);
String *fxp_lookup_type_description(FxP_Lookup *literal);

#endif
