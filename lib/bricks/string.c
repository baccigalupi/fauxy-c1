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

  string_offset(string)     = 0;
  string_length(string)     = 0;
  string_capacity(string)   = capacity;
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

  string_length(string) = length;
  string_offset(string) = FxB_String_offset(string_real_capacity(string), length);
  STRCPY(string_value(string), str);

  return string;
error:
  return NULL;
}

Boolean string_expand(FxB_String *string, int capacity) {
  int real_capacity = capacity * 2;
  int offset = FxB_String_offset(real_capacity, string_length(string));
  CHAR *original = string__value(string);
  CHAR *value = calloc(real_capacity, sizeof(CHAR));

  STRCPY(value + offset, string_value(string));
  verify_memory(value);
  string->value = value;
  string_offset(string) = offset;
  string_capacity(string) = capacity;

  fx_pfree(original);
  return true;
error:
  return false;
}

Boolean string_push_char(FxB_String *string, CHAR c) {
  if ( !(string_length(string) < string_capacity(string)) ) {
    int capacity = FxB_Expandable_capacity(string_length(string));
    Boolean success = string_expand(string, capacity);
    verify(success);
  }

  string_value(string)[string_length(string)] = c;
  string_length(string)++;
  string_value(string)[string_length(string)] = '\0'; // just in case

  return true;
error:
  return false;
}

Boolean string_add_chars(FxB_String *string, CHAR *str) {
  int added_offset = STRLEN(str);
  int i;
  for (i = 0; i < added_offset; i++) {
    verify(string_push_char(string, str[i]));
  }

  return true;
error:
  return false;
}

Boolean string_add_string(FxB_String *string, FxB_String *addition) {
  return string_add_chars(string, string_value(addition));
}

FxB_String *string_duplicate(FxB_String *original) {
  FxB_String *duplicate = FxB_String_create(string_value(original));
  verify(duplicate);
  return duplicate;
error:
  return NULL;
}

Boolean string_unshift_char(FxB_String *string, CHAR c) {
  if ( string_offset(string) < 1 ) {
    int capacity = FxB_Expandable_capacity(string_length(string));
    Boolean success = string_expand(string, capacity);
    verify(success);
  }

  string_offset(string) --;
  string_value(string)[0] = c;
  string_length(string) ++;

  return true;
error:
  return false;
}

Boolean string_unshift_chars(FxB_String *string, CHAR *str) {
  int added_offset = STRLEN(str);
  int i;
  for (i = 0; i < added_offset; i++) {
    verify(string_unshift_char(string, str[i]));
  }

  return true;
error:
  return false;
}

Boolean string_unshift_string(FxB_String *string, FxB_String *addition) {
  return string_unshift_chars(string, string_value(addition));
}

Boolean string_wrap(FxB_String *string, CHAR start_char, CHAR end_char) {
  verify(string_unshift_char(string, start_char));
  verify(string_push_char(string, end_char));

  return true;
error:
  return false;
}


/**
 * Simple Bob Jenkins's hash algorithm taken from the
 * wikipedia description.
 */
Hash string_hash(FxB_String *string) {
  size_t length = string_length(string);
  char *key =     string_value(string);
  Hash hash = 0;
  Hash i = 0;

  for (hash = i = 0; i < length; ++i) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}
