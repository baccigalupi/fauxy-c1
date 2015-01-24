#ifndef __FxB_HashKey_h
#define __FxB_HashKey_h 1

#include <stdlib.h>
#include "string.h"

typedef uint32_t FxB_Hash;

FxB_Hash fxb_string_hash(FxB_String *string);

#endif
