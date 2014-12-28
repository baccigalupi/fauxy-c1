#include "fx_parse.h"
#include "bit.h"

#include "parser_context.h"
#include "lex_wrapper.h"

#include "parse.tab.h" // yyparse
#include "lex.yy.h"    // yylex_init, and yylex_destroy

int parse_stdin() {
  FxParserContext *context = FxParserContext_create();

  FxP_LexWrapper state;
  yylex_init(&state.scanner);

  int status = yyparse(&state, context);

  yylex_destroy(state.scanner);
  // TODO: context free method

  return status;
}
