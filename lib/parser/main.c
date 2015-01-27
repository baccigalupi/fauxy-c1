#include <stdio.h>
#include <stdlib.h>
#include "fx_parse.h"
#include "parser_context.h"
#include "expression_inspect.h"


int main(int argc, char **argv) {
  if (argc == 3 && !strcmp(argv[1], "-p")) {
    // parse and inspect statement
    FxP_ParserContext *context = parse_string(argv[2]);
    FxB_String *inspection = fxp_parser_inspect(context);

    printf("%s\n", fxb_string_value(inspection));
  } else {
    // repl type thing
    printf("\nFauxy -> Go!\n\n");
    FxP_ParserContext *context = NULL;

    while(!context || fxp_parser_context_status(context)) {
      context = parse_stdin();
      verify(context);
      fxp_parser_context_free(context);
    }
  }

  return 0;
error:
  return 1;
}
