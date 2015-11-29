#include <stdio.h>
#include <stdlib.h>
#include "fx_parse.h"
#include "parser_context.h"
#include "expression_inspect.h"

int main(int argc, char **argv) {
  FxP_ParserContext *context = NULL;

  if (argc == 3) {
    char *command = argv[1];
    char *data = argv[2];

    if (!strcmp(command, "-p")) {
      // parse and inspect statement
      context = parse_string(data);
    } else if (!strcmp(command, "-f")) {
      // parse from file and inspect statement
      char *content = read_file(data);
      if (!content) {
        printf("file not found %s\n", data);
      } else {
        printf("%s\n", content);
        context = parse_string(content);
      }
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
      verify(context);
      fxp_parser_context_free(context);
    }
  }

  return fxp_parser_context_error_code(context);
error:
  return context ? fxp_parser_context_error_code(context) : 1;
}
