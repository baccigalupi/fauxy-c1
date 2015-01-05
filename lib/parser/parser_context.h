#ifndef __FxP_ParserContext
#define __FxP_ParserContext 1

#include "../bricks/list.h"

typedef List FxP_ParserContext;

#include "expressions.h"

#define fxp_parser_context_push(C, V)    list_push(C, V)
#define fxp_parser_context_pop(C)        ((FxP_Expressions *)list_pop(C))
#define fxp_parser_current_context(C)    list_last(C)
#define fxp_parser_push_expression(C, V) (fxp_expression_push((FxP_Expressions *)fxp_parser_current_context(C), V))

FxP_ParserContext *FxP_ParserContext_create();

#endif
