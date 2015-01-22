#include "../bricks/helpers.h"
#include "exception.h"

FxP_Exception *FxP_Exception_create(int code, FxB_String *message) {
  FxP_Exception *exception = fx_alloc(FxP_Exception);
  verify_memory(exception);

  fxp_exception_code(exception) = code;
  fxp_exception_message(exception) = message;

  return exception;
error:
  return NULL;
}
