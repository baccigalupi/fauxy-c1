#ifndef __FxP_ParserContext
#define __FxP_ParserContext 1

#include "../bricks/list.h"

typedef List FxP_ParserContext;

#include "expressions.h"

#define fxp_parser_context_push(C, V)    list_push(C, V)
#define fxp_parser_context_pop(C)        ((FxP_Expressions *)list_pop(C, V))
#define fxp_parser_context_current(C)    ((FxP_Expressions *)list_last(C))

FxP_ParserContext *FxP_ParserContext_create();

#endif
