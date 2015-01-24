#include "hash_key.h"

/**
* Simple Bob Jenkins's hash algorithm taken from the
* wikipedia description.
*/
FxB_Hash fxb_string_hash(FxB_String *string) {
  size_t length = string_length(string);
  char *key =     string_value(string);
  FxB_Hash hash = 0;
  FxB_Hash i = 0;

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
