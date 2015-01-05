#include "../bricks/helpers.h"

#include "parser_context.h"
#include "expressions.h"

FxP_ParserContext *FxP_ParserContext_create() {
  FxP_ParserContext *context = List_create();
  verify(context);

  FxP_Expressions *expressions = FxP_Expressions_create();
  verify(expressions);

  list_push(context, expressions);

  return context;
error:
  if (context) { fx_pfree(context); }
  return NULL;
}
