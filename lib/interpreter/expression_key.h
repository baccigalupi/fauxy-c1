#ifndef __expression_key_h
#define __expression_key_h 1

#include "../parser/_parser.h"

char *fxi_type_key(FxP_Expression *expression);
char *fxi_literal_key(FxP_Literal *literal);
char *fxi_lookup_key(FxP_Lookup *lookup);

#endif
