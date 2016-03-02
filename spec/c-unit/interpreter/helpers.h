#include "../../../src/interpreter/class.h"
#include "../../../src/interpreter/method_group.h"
#include "../../../src/interpreter/interpreter.h"
#include "../../../src/interpreter/object.h"
#include "../../../src/interpreter/expression_eval.h"
#include "../../../src/interpreter/native_registry.h"

#include "../../../src/native/boolean_methods.h"
#include "../../../src/native/object_methods.h"
#include "../../../src/native/integer_methods.h"

#include "../../../src/parser/expressions.h"
#include "../../../src/parser/expression_inspect.h"

#include "../../../src/bricks/string.h"
#include "../../../src/bricks/hash_map.h"
#include "../../../src/bricks/list.h"

#include "../lib/spec.h"

#define setup_interpreter()   FxI_Interpreter *interpreter = FxI_Interpreter_create();  \
                              fxi_interpreter_setup(interpreter);

void *print_keys(FxB_HashMap *hash_map) {
  FxB_Array *keys = fxb_hash_map_keys(hash_map);
  int i;
  char *key;
  puts("printing keys:");
  for (i = 0; i < fxb_array_length(keys); i++) {
    key = fxb_array_at_index(keys, i);
    printf("'%s', %p\n", key, key);
  }
}
