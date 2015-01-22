#ifndef __FxB_JsonGen_h
#define __FxB_JsonGen_h 1

#include "string.h"
#include "array.h"

FxB_String *json_gen_bald_pair(FxB_String *key, FxB_String *value);
FxB_String *json_gen_join_pairs(FxB_Array *pairs, char *joiner);
FxB_String *json_gen_wrap_pairs(FxB_Array *pairs);
FxB_String *json_gen_wrap_array_pairs(FxB_Array *pairs);

#endif
