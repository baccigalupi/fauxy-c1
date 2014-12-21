#include "fx_parse.h"
#include "object.h"

#include "expressions.h"
#include "parser_state.h"

#include "parse.tab.h" // yyparse
#include "lex.yy.h"    // yylex_init, and yylex_destroy

int parse_stdin() {
  FxExpressions *expressions = Array_create(1000);

  FxParserState state;
  yylex_init(&state.scanner);

  int status = yyparse(&state, expressions);

  yylex_destroy(state.scanner);
  fx_expressions_free(expressions);

  return status;
}
