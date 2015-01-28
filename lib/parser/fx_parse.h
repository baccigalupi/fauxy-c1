#ifndef __fx_parse
#define __fx_parse 1

#include "parser_context.h"
#include "lex_wrapper.h"

FxP_ParserContext *parse_stdin();
FxP_ParserContext *parse_string(char *str);

FxP_ParserContext *parse_with_state(FxP_LexWrapper state);

char *read_file(char *file_name);

#endif
