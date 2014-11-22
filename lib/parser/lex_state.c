#include <stdlib.h>
#include "lex_state.h"

#include "../bricks/error_handling.h"

LexState *LexState_create() {
  LexState *state = calloc(1, sizeof(LexState));
  check_mem(state);

  state->line = 1;
  state->column = 1;

  return state;
error:
  return NULL;
}
