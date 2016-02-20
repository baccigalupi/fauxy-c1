#include <stdlib.h>

#include "node.h"
#include "helpers.h"

FxB_Node *FxB_Node_create(void *value) {
  FxB_Node *node = fx_alloc(FxB_Node);
  verify_memory(node);
  fxb_node_value(node) = value;
  return node;
error:
  return NULL;
}
