#include <stdlib.h>

#include "helpers.h"
#include "expandable.h"
#include "string.h"

String *String_create_with_capacity(int capacity) {
  String *string = fx_alloc(String);
  verify_memory(string);

  CHAR *value = calloc(capacity + 1, sizeof(CHAR));
  verify_memory(value);

  string_length(string) = 0;
  string_capacity(string)  = capacity;
  string_value(string)  = value;

  return string;
error:
  if (string) { fx_pfree(string); }
  return NULL;
}

String *String_create(CHAR *str) {
  int length = STRLEN(str);
  int capacity = Expandable_capacity(length);
  String *string = String_create_with_capacity(capacity);
  verify_memory(string);

  string_length(string) = length;
  STRCPY(string_value(string), str);

  return string;
error:
  return NULL;
}

void string_push(String *string, CHAR c) {
  if ( !(string_length(string) < string_capacity(string)) ) {
    int capacity = Expandable_capacity(string_length(string));
    Boolean success = string_expand(string, capacity);
    verify(success);
  }

  string_value(string)[string_length(string)] = c;
  string_length(string)++;
  string_value(string)[string_length(string)] = '\0'; // just in case
error:
  return;
}

Boolean string_expand(String *string, int capacity) {
  CHAR *value = realloc(string_value(string), sizeof(CHAR)*capacity);
  verify_memory(value);
  string_value(string) = value;
  string_capacity(string) = capacity;

  return true;
error:
  return false;
}

void string_concat(String *string, CHAR *str) {
  int needed_length = STRLEN(str) + string_length(string);

  if ( !(needed_length < string_capacity(string)) ) {
    int capacity = Expandable_capacity(needed_length);
    Boolean success = string_expand(string, capacity);
    verify(success);
  }

  STRCAT(string_value(string), str);
  string_length(string) = needed_length;
  string_value(string)[string_length(string)] = '\0'; // just in case
error:
  return;
}

void string_add(String *string, String *addition) {
  string_concat(string, string_value(addition));
}

/**
 * Simple Bob Jenkins's hash algorithm taken from the
 * wikipedia description.
 */
Hash string_hash(String *string) {
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
