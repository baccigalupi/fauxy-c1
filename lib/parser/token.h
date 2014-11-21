#ifndef __fauxy_token
#define __fauxy_token

#include <stdlib.h>
#include <string.h>

#include "../bricks/string.h"
#include "../bricks/number.h"

typedef enum {
  FX_NOT_A_TOKEN,               // NULL state for iffiness

  FX_TOKEN_NUMBER,
  FX_TOKEN_STRING,
  FX_TOKEN_REGEX,
  FX_TOKEN_ATOM,                // starts with :

  FX_TOKEN_CLASS_ID,            // starts with uppercase
  FX_TOKEN_ID,                  // method calls and variable names

  FX_TOKEN_LINE_END,            // "\n"
  FX_TOKEN_STATEMENT_END,       // ";"

  FX_TOKEN_ATTRIBUTE_SELECTOR,  // "."
  FX_TOKEN_GROUP_START,         // "("
  FX_TOKEN_GROUP_END,           // ")"
  FX_TOKEN_COMMA,               // ","
  FX_TOKEN_LOCAL_SETTER,        // "="
  FX_TOKEN_ATTRIBUTE_SETTER,    // ":"
  FX_TOKEN_BLOCK_START,         // "{"
  FX_TOKEN_BLOCK_END,           // "}"
  FX_TOKEN_DEFERRED_ARGUMENT,   // "_"

  FX_TOKEN_BLOCK_DECLARATION    // "->"

} TokenType;


typedef struct Token {
  TokenType  type;
  void       *value;
  int        line;
  int        column;
  //   TODO: file_id
} Token;

#define token_line(T)           ((T)->line)
#define token_column(T)         ((T)->column)
#define token_type(T)           ((T)->type)
#define token_value(T)          ((T)->value)

#define token_free(T)           (                                               \
                                  T && (                                        \
                                    (                                           \
                                      token_value(T) &&                         \
                                      (string_free(token_value(T)))             \
                                    ),                                          \
                                    (pfree(T))                                  \
                                  )                                             \
                                )

Token *Token_create(String *value, int line, int column);

#define token_number_value(T)   (number_value((Number *)((T)->value)))
#define token_number_type(T)    (object_type((Number *)object_value(token)))
#define token_string_value(T)   (string_value((String *)((T)->value)))

#endif
