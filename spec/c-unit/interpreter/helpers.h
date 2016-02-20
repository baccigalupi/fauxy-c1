#include "../../../lib/interpreter/class.h"
#include "../../../lib/interpreter/method_group.h"
#include "../../../lib/interpreter/interpreter.h"
#include "../../../lib/interpreter/object.h"
#include "../../../lib/interpreter/literal.h"
#include "../../../lib/interpreter/expression_eval.h"
#include "../../../lib/interpreter/expression_key.h"
#include "../../../lib/interpreter/native_registry.h"

#include "../../../lib/native/boolean_methods.h"

#include "../../../lib/parser/expressions.h"
#include "../../../lib/parser/expression_inspect.h"

#include "../../../lib/bricks/string.h"
#include "../../../lib/bricks/hash_map.h"
#include "../../../lib/bricks/list.h"

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
