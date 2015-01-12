#ifndef __fx_parse
#define __fx_parse 1

#include "parser_context.h"

int parse_stdin();
int parse_string(char *str);

int parse_with_state(FxP_LexWrapper state);

#endif
