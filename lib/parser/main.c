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

    if ( fxp_parser_context_status(context) ) {
      printf("%s", string_value(fxp_parser_context_error_message(context)));
    } else {
      String *inspection = fxp_parser_inspect(context);
      verify(inspection);
      printf("%s", string_value(inspection));
      string_free(inspection);
    }

    fxp_parser_context_free(context);

    printf("\n\n");
  }

  return 0;
error:
  return 1;
}
