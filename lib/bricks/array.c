#include <stdlib.h>

#include "expandable.h"
#include "array.h"


Array *Array_create(int capacity) {
  Array *array = calloc(1, sizeof(Array));
  verify_memory(array);
  array_length(array) = 0;
  array_capacity(array)  = capacity;

  void **values = calloc(capacity, sizeof(void *));
  verify_memory(values);
  array->values = values;

  return array;
error:
  if (array) { fx_pfree(array); }
  return NULL;
}

void array_push(Array *array, void *element) {
  if (array_capacity(array) == array_length(array)) {
    int capacity = Expandable_capacity(array_capacity(array));
    Boolean success = array_expand(array, capacity);
    verify(success);
  }

  array_values(array)[array_length(array)] = element;
  array_length(array) ++;
error:
  return;
}

Boolean array_expand(Array *array, int capacity) {
  void **values = realloc(array_values(array), sizeof(void *) * capacity);
  verify_memory(values);
  array_values(array) = values;
  array_capacity(array)  = capacity;

  return true;
error:
  return false;
}

void array_each(Array *array, ArrayIterator f) {
  int i;
  void *element;
  for (i = 0; i < array_length(array); i++) {
    element = array_at_index(array, i);
    f(element);
  }
}

void *array_pop(Array *array) {
  void *value = NULL;

  if (array_length(array) > 0) {
    int index = array_length(array) - 1;
    value = array_at_index(array, index);
    array_at_index(array, index) = NULL;
    array_length(array)--;
  }

  return value;
}

void array_set(Array *array, int index, void *value) {
  if (array_capacity(array) <= index) {
    int capacity = Expandable_capacity(index);
    Boolean success = array_expand(array, capacity);
    verify(success);
  }

  array_at_index(array, index) = value;
  array_length(array) = index + 1;
error:
  return;
}
