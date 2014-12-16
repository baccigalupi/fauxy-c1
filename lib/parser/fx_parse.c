#include "fx_parse.h"
#include "../core/bit.h"
#include "parser_state.h"
#include "parse.tab.h"
#include "lex.yy.h"

int parse_stdin() {
  ParserState state;
  yylex_init(&state.scanner);
  int status = yyparse(&state);
  yylex_destroy(state.scanner);
  return status;
}
