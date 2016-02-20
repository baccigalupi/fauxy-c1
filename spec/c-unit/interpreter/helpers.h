#include "../../../src/interpreter/class.h"
#include "../../../src/interpreter/method_group.h"
#include "../../../src/interpreter/interpreter.h"
#include "../../../src/interpreter/object.h"
#include "../../../src/interpreter/literal.h"
#include "../../../src/interpreter/expression_eval.h"
#include "../../../src/interpreter/expression_key.h"
#include "../../../src/interpreter/native_registry.h"

#include "../../../src/native/boolean_methods.h"

#include "../../../src/parser/expressions.h"
#include "../../../src/parser/expression_inspect.h"

#include "../../../src/bricks/string.h"
#include "../../../src/bricks/hash_map.h"
#include "../../../src/bricks/list.h"

#include "../lib/spec.h"

#define setup_interpreter()   FxB_HashMap *config = create_pool_config();                     \
                              FxI_Interpreter *interpreter = FxI_Interpreter_create(config);  \
                              fxi_interpreter_setup(interpreter);

FxB_HashMap *create_pool_config() {
  // really small inefficient pool
  FxB_HashMap *config = FxB_HashMap_create(1);
  int *capacity = fx_alloc(int);
  *capacity = 1;
  fxb_hash_map_set(config, "literal_capacity", capacity);
  fxb_hash_map_set(config, "global_capacity", capacity);
  return config;
}

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
