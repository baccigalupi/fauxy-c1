#ifndef __FxP_Expression_inspect
#define __FxP_Expression_inspect 1

#include "../bricks/string.h"
#include "expressions.h"

void   *fxp_inspect(void *element); // void * for use in array iterators

String *fxp_literal_inspect(  FxP_Expression *expression);
String *fxp_lookup_inspect(   FxP_Expression *expression);
String *fxp_collection_inspect(     FxP_Expression *expression);
// typedef FxP_Expression FxP_Method;
// String *fxp_function_inpect( FxP_function *expression);
// typedef FxP_Expression FxP_LocalAssign;
// typedef FxP_Expression FxP_ColonExpression;

String *fxp_expression_type_description(FxP_Expression *expression);
String *fxp_literal_class_description(FxP_Literal *literal);
String *fxp_lookup_type_description(FxP_Lookup *literal);

#endif
