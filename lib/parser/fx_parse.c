#include "fx_parse.h"
#include "../core/bit.h"
#include "parser_state.h"
#include "expressions.h"
#include "parse.tab.h"
#include "lex.yy.h"

int parse_stdin() {
  FxExpressions *expressions = FxExpressions_create(1000);

  FxParserState state;
  yylex_init(&state.scanner);

  int status = yyparse(&state, expressions);

  yylex_destroy(state.scanner);
  fx_expressions_free(expressions);

  return status;
}
