#include <stdlib.h>

#include "expandable.h"
#include "array.h"


FxB_Array *FxB_Array_create(int capacity) {
  FxB_Array *array = calloc(1, sizeof(FxB_Array));
  verify_memory(array);
  fxb_array_length(array) = 0;
  fxb_array_capacity(array)  = capacity;

  void **values = calloc(capacity, sizeof(void *));
  verify_memory(values);
  array->values = values;

  return array;
error:
  if (array) { fx_pfree(array); }
  return NULL;
}

void fxb_array_push(FxB_Array *array, void *element) {
  if (fxb_array_capacity(array) == fxb_array_length(array)) {
    int capacity = FxB_Expandable_capacity(fxb_array_capacity(array));
    Boolean success = fxb_array_expand(array, capacity);
    verify(success);
  }

  fxb_array_values(array)[fxb_array_length(array)] = element;
  fxb_array_length(array) ++;
error:
  return;
}

Boolean fxb_array_expand(FxB_Array *array, int capacity) {
  void **values = realloc(fxb_array_values(array), sizeof(void *) * capacity);
  verify_memory(values);
  fxb_array_values(array) = values;
  fxb_array_capacity(array)  = capacity;

  return true;
error:
  return false;
}

void fxb_array_each(FxB_Array *array, FxB_ArrayIterator f) {
  int i;
  void *element;
  for (i = 0; i < fxb_array_length(array); i++) {
    element = fxb_array_at_index(array, i);
    f(element);
  }
}

void fxb_array_reverse_each(FxB_Array *array, FxB_ArrayIterator f) {
  int i;
  void *element;
  for (i = fxb_array_length(array) - 1; i >= 0; i--) {
    element = fxb_array_at_index(array, i);
    f(element);
  }
}

FxB_Array *fxb_array_map(FxB_Array *array, FxB_ArrayMapIterator f) {
  FxB_Array *mapped = FxB_Array_create(fxb_array_length(array));
  int i;
  void *element;
  for (i = 0; i < fxb_array_length(array); i++) {
    element = fxb_array_at_index(array, i);
    fxb_array_set(mapped, i, f(element));
  }

  return mapped;
}

FxB_Array *fxb_array_reverse_map(FxB_Array *array, FxB_ArrayMapIterator f) {
  FxB_Array *mapped = FxB_Array_create(fxb_array_length(array));
  int i;
  void *element;
  for (i = fxb_array_length(array) - 1; i >= 0; i--) {
    element = fxb_array_at_index(array, i);
    fxb_array_push(mapped, f(element));
  }

  return mapped;
}

void *fxb_array_pop(FxB_Array *array) {
  void *value = NULL;

  if (fxb_array_length(array) > 0) {
    int index = fxb_array_length(array) - 1;
    value = fxb_array_at_index(array, index);
    fxb_array_at_index(array, index) = NULL;
    fxb_array_length(array)--;
  }

  return value;
}

void fxb_array_set(FxB_Array *array, int index, void *value) {
  if (fxb_array_capacity(array) <= index) {
    int capacity = FxB_Expandable_capacity(index);
    Boolean success = fxb_array_expand(array, capacity);
    verify(success);
  }

  fxb_array_at_index(array, index) = value;
  if (fxb_array_length(array) < index + 1) {
    fxb_array_length(array) = index + 1;
  }
error:
  return;
}
