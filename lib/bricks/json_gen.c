#include "json_gen.h"

String *json_gen_bald_pair(String *key, String *value) {
  if (string_value(key)[0] != '"') {
    string_wrap(key, '"', '"');
  }

  String *pair = String_create(string_value(key));
  verify(pair);
  verify(string_add_chars(pair, ": "));
  verify(string_add_string(pair, value));

  return pair;
error:
  return NULL;
}


String *json_gen_wrap_pairs(int n, ...) {
  String *json = String_create_blank();
  verify(json);

  va_list args;
  va_start(args, n);

  int i;
  for (i = 0; i < n; i++) {
    String *pair = va_arg(args, String *);
    verify(string_add_string(json, pair));
    if (i < n-1) {
      verify(string_add_chars(json, ", "));
    }
  }

  va_end(args);

  verify(string_wrap(json, '{', '}'));
  return json;
error:
  return NULL;
}
