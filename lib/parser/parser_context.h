#ifndef __FxP_ParserContext
#define __FxP_ParserContext 1

#include "../bricks/list.h"
#include "exception.h"

typedef struct FxP_ParserContext {
  FxB_List *list;
  FxP_Exception *exception;
} FxP_ParserContext;

#include "expressions.h"

#define fxp_parser_context_list(C)          ((C)->list)
#define fxp_parser_context_execption(C)     ((C)->exception)
#define fxp_parser_context_status(C)        ((C)->exception ? fxp_exception_code((C)->exception) : 0)
#define fxp_parser_context_error_message(C) ((C)->exception ? fxp_exception_message((C)->exception) : NULL)

#define fxp_parser_context_push(C, V)    fxb_list_push(fxp_parser_context_list(C), V)
#define fxp_parser_context_pop(C)        ((FxP_Expressions *)fxb_list_pop(fxp_parser_context_list(C)))
#define fxp_parser_current_context(C)    fxb_list_last(fxp_parser_context_list(C))
#define fxp_parser_push_expression(C, V) (fxp_expression_push((FxP_Expressions *)fxp_parser_current_context(C), V))

#define fxp_parser_inspect(C)            fxp_inspect(fxp_parser_current_context(C))

FxP_ParserContext *FxP_ParserContext_create();
void fxp_parser_context_free(FxP_ParserContext *context);

#endif
