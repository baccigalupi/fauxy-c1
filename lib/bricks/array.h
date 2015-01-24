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

#define fxb_array_length(A)      ((A)->length)
#define fxb_array_capacity(A)    ((A)->capacity)
#define fxb_array_values(A)      ((A)->values)
#define fxb_array_at_index(A, I) (fxb_array_values(A)[I])
#define fxb_array_get(A, I)      fxb_array_at_index(A, I)
#define fxb_array_free(A)        ((fx_pfree(fxb_array_values(A))), (fx_pfree(A)))
#define fxb_array_free_each(A)   (fxb_array_each(A, free)) // macro cannot handle pfree :(
#define fxb_array_r_free(A)      (fxb_array_free_each(A), fxb_array_free(A))

FxB_Array     *FxB_Array_create(int capacity);
void          fxb_array_push(FxB_Array *array, void *element);
Boolean       fxb_array_expand(FxB_Array *array, int seed);
void          fxb_array_each(FxB_Array *array, FxB_ArrayIterator f);
void          fxb_array_reverse_each(FxB_Array *array, FxB_ArrayIterator f);
FxB_Array     *fxb_array_map(FxB_Array *array, FxB_ArrayMapIterator f);
FxB_Array     *fxb_array_reverse_map(FxB_Array *array, FxB_ArrayMapIterator f);
void          *fxb_array_pop(FxB_Array *array);
void          fxb_array_set(FxB_Array *array, int index, void *value);

#endif
