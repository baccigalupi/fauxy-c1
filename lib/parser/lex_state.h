#ifndef __fauxy_lex_state
#define __fauxy_lex_state

typedef struct LexState {
  int line;
  int column;
} LexState;

#define parse_state_line(P)             ((P)->line)
#define parse_state_column(P)           ((P)->column)

LexState *LexState_create();

#endif
