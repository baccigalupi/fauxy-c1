#include "fx_parse.h"
#include "../bricks/array.h"
#include "../core/bit.h"
#include "parser_state.h"
#include "parse.tab.h"
#include "lex.yy.h"

int parse_stdin() {
  ParserState state;
  Array *stack = Array_create(1000);
  yylex_init(&state.scanner);
  int status = yyparse(&state, stack);
  yylex_destroy(state.scanner);
  array_free(stack);
  return status;
}
