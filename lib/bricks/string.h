#ifndef __bricks_string
#define __bricks_string

#include <string.h>
#include <stdlib.h>
#include "bricks.h"

#define CHAR      char
#define STRLEN    strlen
#define STRCPY    strcpy
#define STRCAT    strcat

typedef struct String {
  int length;
  int capacity;

  CHAR *value;
} String;

typedef uint32_t Hash;

#define string_length(S)      ((S)->length)
#define string_capacity(S)    ((S)->capacity)
#define string_value(S)       ((S)->value)
#define string_free(S)        ((pfree(string_value((String *)S))), (pfree(S)))
#define string_char_at(S, I)  ((string_length(S) > I) ? (string_value(S)[I]) : '\0')
#define string_empty(S)       (string_length(S) == 0)
#define strings_equal(S1, S2) (strcmp(string_value(S1), string_value(S2)) == 0)

String        *String_create(CHAR *value);
void           string_push(String *string, CHAR c);
void           string_concat(String *string, CHAR *str);
Boolean        string_expand(String *string, int length);
Hash           string_hash(String *string);

#endif
