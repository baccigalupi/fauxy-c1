#include "helpers.h"

#include "hash_map.h"
#include "list.h"

FxB_HashMap *FxB_HashMap_create(int capacity) {
  FxB_HashMap *hash_map = calloc(1, sizeof(Hash));
  verify_memory(hash_map);

  fxb_hash_map_capacity(hash_map) = capacity;
  fxb_hash_map_values(hash_map) = FxB_Array_create(capacity);
  verify(fxb_hash_map_values(hash_map));

  return hash_map;
error:
  if (hash_map) { fx_pfree(hash_map); }
  return NULL;
}

void *fxb_hash_map_get(FxB_HashMap *hash_map, FxB_String *key) {
  void *value = NULL;
  FxB_Node *node = fxb_hash_map_get_node(hash_map, key);

  if (node) {
    value = node_value(node);
  }

  return value;
}

FxB_Node *fxb_hash_map_get_node(FxB_HashMap *hash_map, FxB_String *key) {
  FxB_Node *current_node = NULL;
  FxB_Node *node = NULL;
  int index = fxb_hash_map_index_for_key(hash_map, key);
  FxB_List *list = fxb_hash_map_list_at_index(hash_map, index);

  if (!list) { return node; }

  list_each(list, current_node) {
    if ( (node_hash(current_node) == string_hash(key)) && strings_equal(node_key(current_node), key) ) {
      node = current_node;
      break;
    }
  }

  return node;
}

void fxb_hash_map_set(FxB_HashMap *hash_map, FxB_String *key, void *value) {
  int index = fxb_hash_map_index_for_key(hash_map, key);

  // create list if value at index in void
  FxB_List *list = fxb_hash_map_list_at_index(hash_map, index);
  if ( !list ) {
    list = FxB_List_create();
    fxb_array_set(fxb_hash_map_values(hash_map), index, list);
    verify(fxb_hash_map_list_at_index(hash_map, index));
  }

  FxB_Node *node = fxb_hash_map_get_node(hash_map, key);
  if (node) {
    // find node if exists, and reset value
    node_value(node) = value;
  } else {
    // create node
    FxB_List *list = fxb_hash_map_list_at_index(hash_map, index);
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

void fxb_hash_map_free_list_values(FxB_HashMap *hash_map) {
  int i;
  FxB_Array *values = fxb_hash_map_values(hash_map);

  int length = fxb_array_length(values);
  for(i = 0; i < length; i++) {
    FxB_List *list = fxb_array_at_index(values, i);
    if (list) {
      list_free(list);
    }
  }
}
