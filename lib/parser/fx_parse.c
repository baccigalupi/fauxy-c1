#include "../bricks/helpers.h"
#include "../bricks/string.h"

#include <stdio.h>

#include "fx_parse.h"
#include "bit.h"

#include "parser_context.h"
#include "lex_wrapper.h"

#include "parse.tab.h" // yyparse
#include "lex.yy.h"    // yylex_init, and yylex_destroy

FxP_ParserContext *parse_with_state(FxP_LexWrapper state) {
  int status;

  FxP_ParserContext *context = FxP_ParserContext_create();
  verify(context);

  status = yyparse(&state, context);

  if (status) {
    printf("ParseError\n"); // TODO: exceptions
  }

  yylex_destroy(state.scanner);

  return context;
error:
  if (context) { fxp_parser_context_free(context); }
  return NULL;
}

FxP_ParserContext *parse_stdin() {
  FxP_LexWrapper state;
  yylex_init(&state.scanner);

  return parse_with_state(state);
}

FxP_ParserContext *parse_string(char *str) {
  FxP_LexWrapper state;
  yylex_init(&state.scanner);
  yy_scan_string(str, state.scanner);

  return parse_with_state(state);
}

FxP_ParserContext *parse_file(char *file_name) {
  char *content = read_file(file_name);
  verify(content);

  return parse_string(content);
error:
  printf("file not found %s\n", file_name);
  return NULL;
}

char *read_file(char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file) {
    char *line = NULL;
    size_t length = 0;
    int i = 0;
    getline(&line, &length, file);
    FxB_String *contents = FxB_String_create("");
    verify(contents);

    while (line && strlen(line) && i < 11) {
      fxb_string_add_chars(contents, line);
      getline(&line, &length, file);
      i++;
    }

    char *file_contents = fxb_string_value(contents);
    fxb_string_free(contents);

    return file_contents;
  } else {
    return NULL;
  }
error:
  return NULL;
}


