#ifndef __FxB_JsonGen_h
#define __FxB_JsonGen_h 1

#include "string.h"
#include "array.h"

#include <jansson.h>

#define JSON_FLAGS 0
#define generate_json_chars(S)  json_dumps(S, JSON_FLAGS)

// macro that sets flag defaults generate the json, copies to new memory and returns it
#define json_gen(S)   char *raw_json = generate_json_chars(S);                  \
                      char *json = calloc(strlen(raw_json) + 1, sizeof(char));  \
                                                                                \
                      verify_memory(json);                                      \
                      strcpy(json, raw_json);                                   \
                      json_decref(S);

FxB_String *fxb_json_gen_bald_pair(FxB_String *key, FxB_String *value);
FxB_String *fxb_json_gen_join_pairs(FxB_Array *pairs, char *joiner);
FxB_String *fxb_json_gen_wrap_pairs(FxB_Array *pairs);
FxB_String *fxb_json_gen_wrap_array_pairs(FxB_Array *pairs);

#endif
