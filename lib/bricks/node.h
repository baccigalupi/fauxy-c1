#ifndef __bricks_node_h
#define __bricks_node_h

#include "string.h"

typedef struct Node {
  Hash         hash;
  String      *key;

  void        *value;

  struct Node *prev;
  struct Node *next;
  struct Node *parent;
} Node;

// NODE flexibility -------------
// Allows same nodes for trees and lists and hashes
// extra field for parent, hash, and key
#define node_left(N)            ((N)->prev)
#define node_right(N)           ((N)->next)
#define node_prev(N)            ((N)->prev)
#define node_next(N)            ((N)->next)
#define node_parent(N)          ((N)->parent)
#define node_value(N)           ((N)->value)
#define node_hash(N)            ((N)->hash)
#define node_key(N)             ((N)->key)

Node *Node_create(void *value);

#endif
