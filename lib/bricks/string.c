#include <stdlib.h>
#include <math.h>

#include "helpers.h"
#include "expandable.h"
#include "string.h"

FxB_String *FxB_String_create_with_capacity(int capacity) {
  FxB_String *string = fx_alloc(FxB_String);
  verify_memory(string);

  CHAR *value = calloc(capacity*2 + 1, sizeof(CHAR));
  verify_memory(value);

  fxb_string_offset(string)     = 0;
  fxb_string_length(string)     = 0;
  fxb_string_capacity(string)   = capacity;
  string->value             = value;

  return string;
error:
  if (string) { fx_pfree(string); }
  return NULL;
}

int FxB_String_offset(int capacity, int length) {
  return floor((capacity - length)/2);
}

FxB_String *FxB_String_create(CHAR *str) {
  int length = STRLEN(str);
  int capacity = FxB_Expandable_capacity(length);
  FxB_String *string = FxB_String_create_with_capacity(capacity);
  verify(string);

  fxb_string_length(string) = length;
  fxb_string_offset(string) = FxB_String_offset(fxb_string_real_capacity(string), length);
  STRCPY(fxb_string_value(string), str);

  return string;
error:
  return NULL;
}

Boolean fxb_string_expand(FxB_String *string, int capacity) {
  int real_capacity = capacity * 2;
  int offset = FxB_String_offset(real_capacity, fxb_string_length(string));
  CHAR *original = fxb_string__value(string);
  CHAR *value = calloc(real_capacity, sizeof(CHAR));

  STRCPY(value + offset, fxb_string_value(string));
  verify_memory(value);
  string->value = value;
  fxb_string_offset(string) = offset;
  fxb_string_capacity(string) = capacity;

  fx_pfree(original);
  return true;
error:
  return false;
}

Boolean fxb_string_push_char(FxB_String *string, CHAR c) {
  if ( !(fxb_string_length(string) < fxb_string_capacity(string)) ) {
    int capacity = FxB_Expandable_capacity(fxb_string_length(string));
    Boolean success = fxb_string_expand(string, capacity);
    verify(success);
  }

  fxb_string_value(string)[fxb_string_length(string)] = c;
  fxb_string_length(string)++;
  fxb_string_value(string)[fxb_string_length(string)] = '\0'; // just in case

  return true;
error:
  return false;
}

Boolean fxb_string_add_chars(FxB_String *string, CHAR *str) {
  int added_offset = STRLEN(str);
  int i;
  for (i = 0; i < added_offset; i++) {
    verify(fxb_string_push_char(string, str[i]));
  }

  return true;
error:
  return false;
}

Boolean fxb_string_add_string(FxB_String *string, FxB_String *addition) {
  return fxb_string_add_chars(string, fxb_string_value(addition));
}

FxB_String *fxb_string_duplicate(FxB_String *original) {
  FxB_String *duplicate = FxB_String_create(fxb_string_value(original));
  verify(duplicate);
  return duplicate;
error:
  return NULL;
}

Boolean fxb_string_unshift_char(FxB_String *string, CHAR c) {
  if ( fxb_string_offset(string) < 1 ) {
    int capacity = FxB_Expandable_capacity(fxb_string_length(string));
    Boolean success = fxb_string_expand(string, capacity);
    verify(success);
  }

  fxb_string_offset(string) --;
  fxb_string_value(string)[0] = c;
  fxb_string_length(string) ++;

  return true;
error:
  return false;
}

Boolean fxb_string_unshift_chars(FxB_String *string, CHAR *str) {
  int added_offset = STRLEN(str);
  int i;
  for (i = 0; i < added_offset; i++) {
    verify(fxb_string_unshift_char(string, str[i]));
  }

  return true;
error:
  return false;
}

Boolean fxb_string_unshift_string(FxB_String *string, FxB_String *addition) {
  return fxb_string_unshift_chars(string, fxb_string_value(addition));
}

Boolean fxb_string_wrap(FxB_String *string, CHAR start_char, CHAR end_char) {
  verify(fxb_string_unshift_char(string, start_char));
  verify(fxb_string_push_char(string, end_char));

  return true;
error:
  return false;
}
