#ifndef __FxP_Exception
#define __FxP_Exception 1

#include "../bricks/string.h"

typedef struct FxP_Exception {
  int code;
  String *message;
} FxP_Exception;

#define fxp_exception_code(E)    ((E)->code)
#define fxp_exception_message(E) ((E)->message)
#define fxp_exception_free(E)    (string_free(fxp_exception_message(E)), fx_pfree(E))

#endif
