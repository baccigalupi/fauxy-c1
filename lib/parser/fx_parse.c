#include "fx_parse.h"
#include "bit.h"

#include "expressions.h"
#include "lex_wrapper.h"

#include "parse.tab.h" // yyparse
#include "lex.yy.h"    // yylex_init, and yylex_destroy

int parse_stdin() {
  FxExpressions *expressions = FxExpressions_create();

  FxLexWrapper state;
  yylex_init(&state.scanner);

  int status = yyparse(&state, expressions);

  yylex_destroy(state.scanner);
  fx_expressions_free(expressions);

  return status;
}
