#include "json_gen.h"

String *json_gen_bald_pair(String *key, String *value) {
  String *pair = NULL;
  verify(key);
  verify(value);

  if (string_value(key)[0] != '"') {
    string_wrap(key, '"', '"');
  }

  pair = String_create(string_value(key));
  verify(pair);
  verify(string_add_chars(pair, ": "));
  verify(string_add_string(pair, value));

  return pair;
error:
  if (pair) { string_free(pair); }
  return NULL;
}

String *json_gen_join_pairs(FxB_Array *pairs, char *joiner) {
  String *joined = String_create_blank();
  verify(joined);

  int length = array_length(pairs);
  int i;
  for(i = 0; i < length; i++) {
    verify(string_add_string(joined, array_get(pairs, i)));
    if (i < length - 1) {
      verify(string_add_chars(joined, joiner));
    }
  }

  return joined;
error:
  return NULL;
}

String *json_gen_wrap_pairs(FxB_Array *pairs) {
  String *json = json_gen_join_pairs(pairs, ", ");
  verify(json);

  verify(string_wrap(json, '{', '}'));
  return json;
error:
  return NULL;
}

String *json_gen_wrap_array_pairs(FxB_Array *pairs) {
  String *json = json_gen_join_pairs(pairs, ",\n");
  verify(json);
  verify(string_wrap(json, '\n', '\n'));
  verify(string_wrap(json, '[', ']'));
  return json;
error:
  return NULL;
}
