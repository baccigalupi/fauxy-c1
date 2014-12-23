#include <stdlib.h>

#include "node.h"
#include "helpers.h"

Node *Node_create(void *value) {
  Node *node = calloc(1, sizeof(Node));
  verify_memory(node);
  node_value(node) = value;
  return node;
error:
  return NULL;
}
