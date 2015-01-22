#include "helpers.h"

#include "hash_map.h"
#include "list.h"

HashMap *HashMap_create(int capacity) {
  HashMap *hash_map = calloc(1, sizeof(Hash));
  verify_memory(hash_map);

  hash_map_capacity(hash_map) = capacity;
  hash_map_values(hash_map) = FxB_Array_create(capacity);
  verify(hash_map_values(hash_map));

  return hash_map;
error:
  if (hash_map) { fx_pfree(hash_map); }
  return NULL;
}

void *hash_map_get(HashMap *hash_map, String *key) {
  void *value = NULL;
  Node *node = hash_map_get_node(hash_map, key);

  if (node) {
    value = node_value(node);
  }

  return value;
}

Node *hash_map_get_node(HashMap *hash_map, String *key) {
  Node *current_node = NULL;
  Node *node = NULL;
  int index = hash_map_index_for_key(hash_map, key);
  List *list = hash_map_list_at_index(hash_map, index);

  if (!list) { return node; }

  list_each(list, current_node) {
    if ( (node_hash(current_node) == string_hash(key)) && strings_equal(node_key(current_node), key) ) {
      node = current_node;
      break;
    }
  }

  return node;
}

void hash_map_set(HashMap *hash_map, String *key, void *value) {
  int index = hash_map_index_for_key(hash_map, key);

  // create list if value at index in void
  List *list = hash_map_list_at_index(hash_map, index);
  if ( !list ) {
    list = List_create();
    array_set(hash_map_values(hash_map), index, list);
    verify(hash_map_list_at_index(hash_map, index));
  }

  Node *node = hash_map_get_node(hash_map, key);
  if (node) {
    // find node if exists, and reset value
    node_value(node) = value;
  } else {
    // create node
    List *list = hash_map_list_at_index(hash_map, index);
    list_push(list, value);

    // set extra node attributes
    node = list_node_last(list);
    node_hash(node) = string_hash(key);
    node_key(node) = key;
  }

error:
  // TODO: start raising errors on set fails??
  return;
}

void hash_map_free_list_values(HashMap *hash_map) {
  int i;
  FxB_Array *values = hash_map_values(hash_map);

  int length = array_length(values);
  for(i = 0; i < length; i++) {
    List *list = array_at_index(values, i);
    if (list) {
      list_free(list);
    }
  }
}
