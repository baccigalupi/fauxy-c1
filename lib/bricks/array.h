#ifndef __FxB_Array_h
#define __FxB_Array_h 1

#include "helpers.h"

typedef struct FxB_Array {
  int length;
  int capacity;

  void **values;
} FxB_Array;

typedef void  (FxB_ArrayIterator)(void *);
typedef void *(FxB_ArrayMapIterator)(void *);

#define array_length(A)      ((A)->length)
#define array_capacity(A)    ((A)->capacity)
#define array_values(A)      ((A)->values)
#define array_at_index(A, I) (array_values(A)[I])
#define array_get(A, I)      array_at_index(A, I)
#define array_free(A)        ((fx_pfree(array_values(A))), (fx_pfree(A)))
#define array_free_each(A)   (array_each(A, free)) // macro cannot handle pfree :(
#define array_r_free(A)      (array_free_each(A), array_free(A))

FxB_Array     *FxB_Array_create(int capacity);
void       array_push(FxB_Array *array, void *element);
Boolean    array_expand(FxB_Array *array, int seed);
void       array_each(FxB_Array *array, FxB_ArrayIterator f);
void       array_reverse_each(FxB_Array *array, FxB_ArrayIterator f);
FxB_Array     *array_map(FxB_Array *array, FxB_ArrayMapIterator f);
FxB_Array     *array_reverse_map(FxB_Array *array, FxB_ArrayMapIterator f);
void      *array_pop(FxB_Array *array);
void       array_set(FxB_Array *array, int index, void *value);

#endif
