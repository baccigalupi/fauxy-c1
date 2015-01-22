#include <stdlib.h>

#include "node.h"
#include "helpers.h"

FxB_Node *FxB_Node_create(void *value) {
  FxB_Node *node = calloc(1, sizeof(FxB_Node));
  verify_memory(node);
  node_value(node) = value;
  return node;
error:
  return NULL;
}
