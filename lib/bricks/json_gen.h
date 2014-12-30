#ifndef __json_gen_h
#define __json_gen_h

#include <stdarg.h>
#include "string.h"

String *json_gen_bald_pair(String *key, String *value);
String *json_gen_wrap_pairs(int n, ...);

#endif
