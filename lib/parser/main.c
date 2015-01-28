#include <stdio.h>
#include <stdlib.h>
#include "fx_parse.h"
#include "parser_context.h"
#include "expression_inspect.h"


int main(int argc, char **argv) {
  if (argc == 3) {
    char *command = argv[1];
    char *data = argv[2];
    if (!strcmp(command, "-p")) {
      // parse and inspect statement
      FxP_ParserContext *context = parse_string(data);
      FxB_String *inspection = fxp_parser_inspect(context);
      printf("%s\n", fxb_string_value(inspection));
    } else if (!strcmp(command, "-f")) {
      // parse from file and inspect statement
      FILE *file = fopen(data, "r");
      if (file) {
        char *line = NULL;
        size_t length = 0;
        int i = 0;
        getline(&line, &length, file);
        FxB_String *contents = FxB_String_create("");
        printf("%s\n", line);

        while (line && strlen(line) && i < 11) {
          fxb_string_add_chars(contents, line);
          fxb_string_push_char(contents, '\n');
          getline(&line, &length, file);
          i++;
        }

        FxP_ParserContext *context = parse_string(fxb_string_value(contents));
        FxB_String *inspection = fxp_parser_inspect(context);
        printf("%s\n", fxb_string_value(inspection));
      } else {
        printf("file not found %s\n", data);
      }
    }
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
