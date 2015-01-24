#include "../bricks/helpers.h"

#include "fx_parse.h"
#include "bit.h"

#include "parser_context.h"
#include "lex_wrapper.h"

#include "parse.tab.h" // yyparse
#include "lex.yy.h"    // yylex_init, and yylex_destroy

FxP_ParserContext *parse_with_state(FxP_LexWrapper state) {
  FxP_Exception *exception = NULL;
  FxB_String *error_message    = NULL;
  int status;

  FxP_ParserContext *context = FxP_ParserContext_create();
  verify(context);

  status = yyparse(&state, context);

  if (status) {
    error_message = FxB_String_create("Parse Error");
    verify(error_message);
    exception = FxP_Exception_create(status, error_message);
    verify(exception);
    fxp_parser_context_execption(context) = exception;
  }

  yylex_destroy(state.scanner);

  return context;
error:
  if (context) { fxp_parser_context_free(context); }
  if (error_message) { fxb_string_free(error_message); }
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
