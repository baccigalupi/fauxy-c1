#include "../bricks/helpers.h"
#include "../bricks/list.h"

#include "parser_context.h"
#include "expressions.h"

FxP_ParserContext *FxP_ParserContext_create() {
  FxP_ParserContext *context = fx_alloc(FxP_ParserContext);
  verify(context);

  List *list = List_create();
  verify(list);
  fxp_parser_context_list(context) = list;

  FxP_Expressions *expressions = FxP_Expressions_create();
  verify(expressions);

  list_push(list, expressions);

  return context;
error:
  if (context)  { fx_pfree(context); }
  if (list)     { list_free(context); }
  return NULL;
}
