#ifndef __FxB_JsonGen_h
#define __FxB_JsonGen_h 1

#include "string.h"
#include "array.h"

#include <jansson.h>

#define JSON_FLAGS JSON_INDENT(2) | JSON_PRESERVE_ORDER
#define generate_json_chars(S)  json_dumps(S, JSON_FLAGS)

// macro that sets flag defaults generate the json, copies to new memory and returns it
#define json_gen(S)   char *raw_json = generate_json_chars(S);                  \
                      char *json = calloc(strlen(raw_json) + 1, sizeof(char));  \
                                                                                \
                      verify_memory(json);                                      \
                      strcpy(json, raw_json);                                   \
                      json_decref(S);

#endif
