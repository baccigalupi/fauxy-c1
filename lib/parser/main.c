#include <stdio.h>
#include <stdlib.h>
#include "fx_parse.h"
#include "parser_context.h"
#include "expression_inspect.h"


int main() {
  printf("\nFauxy -> Go!\n\n");
  FxP_ParserContext *context = NULL;

  while(!context || fxp_parser_context_status(context)) {
    context = parse_stdin();
    verify(context);
    fxp_parser_context_free(context);
  }

  return 0;
error:
  return 1;
}
