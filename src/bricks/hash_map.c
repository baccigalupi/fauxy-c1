#include "helpers.h"

#include "hash_map.h"
#include "json_gen.h"
#include "list.h"

#include <math.h>
#include <jansson.h>

FxB_HashMap *FxB_HashMap_create(int capacity) {
  FxB_HashMap *hash_map = fx_alloc(FxB_Hash);
  verify_memory(hash_map);

  fxb_hash_map_capacity(hash_map) = capacity;
  fxb_hash_map_values(hash_map) =   FxB_Array_create(capacity);
  verify(fxb_hash_map_values(hash_map));

  return hash_map;
error:
  if (hash_map) { fx_pfree(hash_map); }
  return NULL;
}

void *fxb_hash_map_get(FxB_HashMap *hash_map, char *key) {
  void *value = NULL;
  FxB_Node *node = fxb_hash_map_get_node(hash_map, key);

  if (node) {
    value = fxb_node_value(node);
  }

  return value;
}

FxB_Node *fxb_hash_map_get_node(FxB_HashMap *hash_map, char *key) {
  FxB_Node *current_node = NULL;
  FxB_Node *node = NULL;
  int index = fxb_hash_map_index_for_key(hash_map, key);
  FxB_List *list = fxb_hash_map_list_at_index(hash_map, index);

  if (!list) { return node; }

  fxb_list_each(list, current_node) {
    if ( (fxb_node_hash(current_node) == fxb_string_hash(key)) && !strcmp(fxb_node_key(current_node), key) ) {
      node = current_node;
      break;
    }
  }

  return node;
}

void fxb_hash_map_set(FxB_HashMap *hash_map, char *key, void *value) {
  int index = fxb_hash_map_index_for_key(hash_map, key);
  FxB_List *list = NULL;

  // create list if value at index in void
  list = fxb_hash_map_list_at_index(hash_map, index);
  if ( !list ) {
    list = FxB_List_create();
    fxb_array_set(fxb_hash_map_values(hash_map), index, list);
    verify(fxb_hash_map_list_at_index(hash_map, index));
  }

  FxB_Node *node = fxb_hash_map_get_node(hash_map, key);
  if (node) {
    // find node if exists, and reset value
    fxb_node_value(node) = value;
  } else {
    node = FxB_Node_create(value);

    // set extra node attributes
    char *dup_key = calloc(strlen(key) + 1, sizeof(char));
    strcpy(dup_key, key);
    fxb_node_hash(node) = fxb_string_hash(dup_key);
    fxb_node_key(node) = dup_key;

    fxb_list_push_node(list, node);
  }

  fxb_hash_map_length(hash_map) ++;
error:
  // TODO: start raising errors on set fails??
  return;
}

FxB_Array *fxb_hash_map_keys(FxB_HashMap *hash_map) {
  int key_length = fxb_hash_map_length(hash_map);
  char *temp_keys[key_length];

  int i;
  int keys_found = 0;
  int length = fxb_hash_map_capacity(hash_map);
  unsigned long max_length = 0;
  FxB_Node *node = NULL;
  FxB_List *fxb_node_list = NULL;
  for (i = 0; i < length; i++) {
    // get list at array index
    fxb_node_list = fxb_hash_map_list_at_index(hash_map, i);
    if (!fxb_node_list) { continue; }
    // iterate through list gathering keys

    fxb_list_each(fxb_node_list, node) {
      char *key = fxb_node_key(node);
      max_length = max_length < strlen(key) ? strlen(key) : max_length;
      temp_keys[keys_found] = key;
      keys_found ++;
    }
  }

  int j;
  char temp[max_length + 1];
  for (i = 0; i < key_length; i++) {
    for (j = 0; j < key_length - 1; j++) {
      if (strcmp(temp_keys[j], temp_keys[j + 1]) > 0) {
        strcpy(temp, temp_keys[j]);
        strcpy(temp_keys[j], temp_keys[j + 1]);
        strcpy(temp_keys[j + 1], temp);
      }
    }
  }

  FxB_Array *keys = FxB_Array_create(key_length);
  verify(keys);

  for (i = 0; i < key_length; i++) {
    fxb_array_push(keys, temp_keys[i]);
  }

  return keys;
error:
  return NULL;
}

void fxb_hash_map_free_list_values(FxB_HashMap *hash_map) {
  int i;
  FxB_Array *values = fxb_hash_map_values(hash_map);

  int length = fxb_array_length(values);
  for(i = 0; i < length; i++) {
    FxB_List *list = fxb_array_at_index(values, i);
    if (list) {
      fxb_list_free(list);
    }
  }
}

CHAR  *fxb_hash_map_inspect(FxB_HashMap *hash_map) {
  json_t *root = json_object();
  json_t *hash_root = json_object();
  json_object_set_new(root, "FxB_HashMap", hash_root);

  int length = fxb_hash_map_capacity(hash_map);
  FxB_Node *node = NULL;
  FxB_List *fxb_node_list = NULL;
  int i;
  for (i = 0; i < length; i++) {
    // bucket number key
    int number_length = (ceil(log10(i))+1)*sizeof(char);
    if (number_length <= 1) { number_length = 2; }
    char number_key[number_length];
    sprintf(number_key, "%d", i);

    fxb_node_list = fxb_hash_map_list_at_index(hash_map, i);

    json_t *json_arr = json_array();
    json_object_set_new(hash_root, number_key, json_arr);

    if (fxb_node_list) {
      fxb_list_each(fxb_node_list, node) {
        char *key = fxb_node_key(node);
        json_array_append(json_arr, json_string(key));
      }
    }
  }

  json_gen(root);

  return json;
error:
  return NULL;
}
