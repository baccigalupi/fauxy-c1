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


#define fxb_string_offset(S)          ((S)->offset)
#define fxb_string_length(S)          ((S)->length)
#define fxb_string_real_capacity(S)   ((S)->capacity)*2
#define fxb_string_capacity(S)        ((S)->capacity)
#define fxb_string__value(S)          ((S)->value)
#define fxb_string_value(S)           ((S)->value + fxb_string_offset(S))
#define fxb_string_free(S)            ((fx_pfree(fxb_string__value((FxB_String *)S))), (fx_pfree(S)))
#define fxb_string_char_at(S, I)      ((fxb_string_length(S) > I) ? (fxb_string_value(S)[I]) : '\0')
#define fxb_string_empty(S)           (fxb_string_length(S) == 0)
#define fxb_strings_equal(S1, S2)     (strcmp(fxb_string_value(S1), fxb_string_value(S2)) == 0)

#define FxB_String_create_blank() FxB_String_create_with_capacity(0);

FxB_String    *FxB_String_create(CHAR *value);
FxB_String    *FxB_String_create_with_capacity(int capacity);
int            FxB_String_offset(int capacity, int length);
Boolean        fxb_string_expand(FxB_String *string, int length);

Boolean        fxb_string_push_char(FxB_String *string, CHAR c);
Boolean        fxb_string_add_chars(FxB_String *string, CHAR *str);
Boolean        fxb_string_add_string(FxB_String *string, FxB_String *addition);

Boolean        fxb_string_unshift_char(FxB_String *string, CHAR c);
Boolean        fxb_string_unshift_chars(FxB_String *string, CHAR *str);
Boolean        fxb_string_unshift_string(FxB_String *string, FxB_String *addition);

FxB_String    *fxb_string_duplicate(FxB_String *original);
Boolean        fxb_string_wrap(FxB_String *original, CHAR start_char, CHAR end_char);

#endif
