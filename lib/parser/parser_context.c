#include "../bricks/helpers.h"

#include "parser_context.h"
#include "expressions.h"

FxParserContext *FxParserContext_create() {
  FxParserContext *context = List_create();
  verify(context);

  FxP_Expressions *expressions = FxP_Expressions_create();
  verify(expressions);

  list_push(context, expressions);
error:
  return NULL;
}
