#ifndef __FxP_Expression_inspect
#define __FxP_Expression_inspect 1

#include "../bricks/string.h"
#include "expressions.h"

String *fxp_literal_inspect(FxP_Literal *literal);
String *fxp_lookup_inspect(FxP_Lookup *literal);

String *fxp_expression_type_description(FxP_Expression *expression);
String *fxp_literal_class_description(FxP_Literal *literal);
String *fxp_lookup_type_description(FxP_Lookup *literal);

#endif
