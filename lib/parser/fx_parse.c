#include "fx_parse.h"
#include "bit.h"

#include "parser_context.h"
#include "lex_wrapper.h"

#include "parse.tab.h" // yyparse
#include "lex.yy.h"    // yylex_init, and yylex_destroy

int parse_with_state(FxP_LexWrapper state) {
  FxP_ParserContext *context = FxP_ParserContext_create();

  int status = yyparse(&state, context);

  yylex_destroy(state.scanner);

  return status;
}

int parse_stdin() {
  FxP_LexWrapper state;
  yylex_init(&state.scanner);

  return parse_with_state(state);
}

int parse_string(char *str) {
  FxP_LexWrapper state;
  yylex_init(&state.scanner);
  yy_scan_string(str, state.scanner);

  return parse_with_state(state);
}
