#include "../bricks/helpers.h"
#include "../bricks/list.h"

#include "parser_context.h"
#include "expressions.h"

FxP_ParserContext *FxP_ParserContext_create() {
  FxB_List *list = NULL;

  FxP_ParserContext *context = fx_alloc(FxP_ParserContext);
  verify_memory(context);

  list = FxB_List_create();
  verify(list);
  fxp_parser_context_list(context) = list;

  FxP_Expressions *expressions = FxP_Expressions_create();
  verify(expressions);

  fxb_list_push(list, expressions);

  return context;
error:
  if (context)  { fx_pfree(context); }
  if (list)     { fxb_list_free(list); }
  return NULL;
}

void fxp_parser_context_free(FxP_ParserContext *context) {
  if (fxp_parser_context_execption(context)) {
    fxp_exception_free(fxp_parser_context_execption(context));
  }

  FxB_Node *node = NULL;
  fxb_list_each(fxp_parser_context_list(context), node) {
    fxp_expression_free(node_value(node));
  }
  fxb_list_free(fxp_parser_context_list(context));

  fx_pfree(context);
}

