#include "../bricks/helpers.h"
#include "../bricks/list.h"

#include "parser_context.h"
#include "expressions.h"

FxP_ParserContext *FxP_ParserContext_create() {
  List *list = NULL;

  FxP_ParserContext *context = fx_alloc(FxP_ParserContext);
  verify_memory(context);

  list = List_create();
  verify(list);
  fxp_parser_context_list(context) = list;

  FxP_Expressions *expressions = FxP_Expressions_create();
  verify(expressions);

  list_push(list, expressions);

  return context;
error:
  if (context)  { fx_pfree(context); }
  if (list)     { list_free(list); }
  return NULL;
}

void fxp_parser_context_free(FxP_ParserContext *context) {
  if (fxp_parser_context_execption(context)) {
    fxp_exception_free(fxp_parser_context_execption(context));
  }

  Node *node = NULL;
  list_each(fxp_parser_context_list(context), node) {
    fxp_expression_free(node_value(node));
  }
  list_free(fxp_parser_context_list(context));

  fx_pfree(context);
}

