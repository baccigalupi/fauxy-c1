#ifndef __fauxy_parser_state
#define __fauxy_parser_state

typedef struct ParserState {
  int line;
  int column;
  void *scanner;
} ParserState;

#define parser_state_line(P)             ((P)->line)
#define parser_state_column(P)           ((P)->column)
#define parser_state_scanner(P)          ((P)->scanner)

#endif
