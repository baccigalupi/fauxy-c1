#ifndef __json_gen_h
#define __json_gen_h

#include "string.h"
#include "array.h"

String *json_gen_bald_pair(String *key, String *value);
String *json_gen_join_pairs(Array *pairs, char *joiner);
String *json_gen_wrap_pairs(Array *pairs);
String *json_gen_wrap_array_pairs(Array *pairs);

#endif
