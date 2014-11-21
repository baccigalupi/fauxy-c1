#include "../bricks/bricks.h"
#include "../bricks/error_handling.h"

#include "token.h"

Token *Token_create(String *value, int line, int column) {
  Token *token = calloc(1, sizeof(Token));
  check_mem(token);

  object_value(token) = value;
  token_line(token) = line;
  token_column(token) = column;

  return token;
  error:
  return NULL;
}
