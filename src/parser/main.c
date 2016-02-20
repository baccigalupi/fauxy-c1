#include <stdio.h>
#include <stdlib.h>
#include "fx_parse.h"
#include "parser_context.h"
#include "expression_inspect.h"

// repl of sorts, plus file parsing
int main(int argc, char **argv) {
  FxP_ParserContext *context = NULL;

  if (argc == 3) {
    char *command = argv[1];
    char *data = argv[2];

    if (!strcmp(command, "-p")) {
      context = parse_string(data);
    } else if (!strcmp(command, "-f")) {
      context = parse_file(data);
    }

    if (context && !fxp_parser_context_error_code(context)) {
      FxB_String *inspection = fxp_parser_inspect(context);
      printf("%s\n", fxb_string_value(inspection));
    }
  } else {
    // repl type thing
    printf("\nFauxy -> Go!\n\n");

    while(!context) {
      context = parse_stdin();
      printf("%s\n", fxp_parser_inspect(context));
      verify(context);
      fxp_parser_context_free(context);
    }
  }

  return fxp_parser_context_error_code(context);
error:
  return context ? fxp_parser_context_error_code(context) : 1;
}
