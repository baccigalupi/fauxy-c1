#ifndef __bricks_string
#define __bricks_string

#include <string.h>
#include <stdlib.h>
#include "helpers.h"

#define CHAR      char
#define STRLEN    strlen
#define STRCPY    strcpy
#define STRCAT    strcat

typedef struct String {
  int length;
  int capacity;
  int offset;

  CHAR *value;
} String;

typedef uint32_t Hash;

#define string_offset(S)      ((S)->offset)
#define string_length(S)      ((S)->length)
#define string_capacity(S)    ((S)->capacity)
#define string__value(S)      ((S)->value)
#define string_value(S)       ((S)->value + string_offset(S))
#define string_free(S)        ((fx_pfree(string__value((String *)S))), (fx_pfree(S)))
#define string_char_at(S, I)  ((string_length(S) > I) ? (string_value(S)[I]) : '\0')
#define string_empty(S)       (string_length(S) == 0)
#define strings_equal(S1, S2) (strcmp(string_value(S1), string_value(S2)) == 0)

#define String_create_blank() String_create_with_capacity(0);

String        *String_create(CHAR *value);
String        *String_create_with_capacity(int capacity);
Boolean        string_push_char(String *string, CHAR c);
Boolean        string_add_chars(String *string, CHAR *str);
Boolean        string_add_string(String *string, String *addition);
Boolean        string_expand(String *string, int length);
String        *string_duplicate(String *original);
Hash           string_hash(String *string);

#endif
