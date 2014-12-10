#include <stdlib.h>
#include "lex_state.h"

#include "../bricks/helpers.h"

LexState *LexState_create() {
  LexState *state = calloc(1, sizeof(LexState));
  verify_memory(state);

  state->line = 1;
  state->column = 1;

  return state;
error:
  return NULL;
}
