#include "json_gen.h"

FxB_String *json_gen_bald_pair(FxB_String *key, FxB_String *value) {
  FxB_String *pair = NULL;
  verify(key);
  verify(value);

  if (string_value(key)[0] != '"') {
    string_wrap(key, '"', '"');
  }

  pair = FxB_String_create(string_value(key));
  verify(pair);
  verify(string_add_chars(pair, ": "));
  verify(string_add_string(pair, value));

  return pair;
error:
  if (pair) { string_free(pair); }
  return NULL;
}

FxB_String *json_gen_join_pairs(FxB_Array *pairs, char *joiner) {
  FxB_String *joined = FxB_String_create_blank();
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

FxB_String *json_gen_wrap_pairs(FxB_Array *pairs) {
  FxB_String *json = json_gen_join_pairs(pairs, ", ");
  verify(json);

  verify(string_wrap(json, '{', '}'));
  return json;
error:
  return NULL;
}

FxB_String *json_gen_wrap_array_pairs(FxB_Array *pairs) {
  FxB_String *json = json_gen_join_pairs(pairs, ",\n");
  verify(json);
  verify(string_wrap(json, '\n', '\n'));
  verify(string_wrap(json, '[', ']'));
  return json;
error:
  return NULL;
}
