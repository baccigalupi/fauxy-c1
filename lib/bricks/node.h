#ifndef __FxB_Node_h
#define __FxB_Node_h 1

#include "string.h"
#include "hash_key.h"

typedef struct FxB_Node {
  FxB_Hash        hash;
  char           *key;

  void           *value;

  struct FxB_Node *prev;
  struct FxB_Node *next;
  struct FxB_Node *parent;
} FxB_Node;

// NODE flexibility -------------
// Allows same nodes for trees and lists and hashes
// extra field for parent, hash, and key
#define fxb_node_left(N)            ((N)->prev)
#define fxb_node_right(N)           ((N)->next)
#define fxb_node_prev(N)            ((N)->prev)
#define fxb_node_next(N)            ((N)->next)
#define fxb_node_parent(N)          ((N)->parent)
#define fxb_node_value(N)           ((N)->value)
#define fxb_node_hash(N)            ((N)->hash)
#define fxb_node_key(N)             ((N)->key)

FxB_Node *FxB_Node_create(void *value);

#endif
