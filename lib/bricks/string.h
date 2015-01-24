#ifndef __FxB_String_h
#define __FxB_String_h 1

#include <string.h>
#include "helpers.h"

#define CHAR      char
#define STRLEN    strlen
#define STRCPY    strcpy
#define STRCAT    strcat

typedef struct FxB_String {
  int length;
  int capacity;
  int offset;

  CHAR *value;
} FxB_String;


#define string_offset(S)          ((S)->offset)
#define string_length(S)          ((S)->length)
#define string_real_capacity(S)   ((S)->capacity)*2
#define string_capacity(S)        ((S)->capacity)
#define string__value(S)          ((S)->value)
#define string_value(S)           ((S)->value + string_offset(S))
#define string_free(S)            ((fx_pfree(string__value((FxB_String *)S))), (fx_pfree(S)))
#define string_char_at(S, I)      ((string_length(S) > I) ? (string_value(S)[I]) : '\0')
#define string_empty(S)           (string_length(S) == 0)
#define strings_equal(S1, S2)     (strcmp(string_value(S1), string_value(S2)) == 0)

#define FxB_String_create_blank() FxB_String_create_with_capacity(0);

FxB_String    *FxB_String_create(CHAR *value);
FxB_String    *FxB_String_create_with_capacity(int capacity);
int            FxB_String_offset(int capacity, int length);
Boolean        string_expand(FxB_String *string, int length);

Boolean        string_push_char(FxB_String *string, CHAR c);
Boolean        string_add_chars(FxB_String *string, CHAR *str);
Boolean        string_add_string(FxB_String *string, FxB_String *addition);

Boolean        string_unshift_char(FxB_String *string, CHAR c);
Boolean        string_unshift_chars(FxB_String *string, CHAR *str);
Boolean        string_unshift_string(FxB_String *string, FxB_String *addition);

FxB_String    *string_duplicate(FxB_String *original);
Boolean        string_wrap(FxB_String *original, CHAR start_char, CHAR end_char);

// TODO: move somewhere else??


#endif
