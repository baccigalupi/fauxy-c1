#ifndef __FxB_JsonGen_h
#define __FxB_JsonGen_h

#include "string.h"
#include "array.h"

String *json_gen_bald_pair(String *key, String *value);
String *json_gen_join_pairs(FxB_Array *pairs, char *joiner);
String *json_gen_wrap_pairs(FxB_Array *pairs);
String *json_gen_wrap_array_pairs(FxB_Array *pairs);

#endif
