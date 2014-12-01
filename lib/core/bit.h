#ifndef __FauxyBit
#define __FauxyBit

typedef struct {
  int type;
  float value;
} FauxyBitFloat;

typedef struct {
  int type;
  int value;
} FauxyBitInteger;

enum {
  FX_BIT_FLOAT,
  FX_BIT_INTEGER,
  FX_BIT_STRING
};

typedef struct {
  int type;
  void *value;
} FauxyBit;

#define fauxy_bit_type(F)     ((F)->type)
#define fauxy_bit__value(F)   ((F)->value)

#define fauxy_bit_value(F)    ((fauxy_bit_type(F) == FX_BIT_INTEGER) ?          \
                                ((FauxyBitInteger *)(fauxy_bit__value(F))) :    \
                                ((fauxy_bit_type(F) == FX_BIT_FLOAT) ?          \
                                  ((FauxyBitFloat *)(fauxy_bit__value(F))) :    \
                                  ((FauxyBitString *)(fauxy_bit__value(F)))     \
                                )                                               \
                              )

FauxyBit *FauxyBit_create(int token_type, char *text);

#endif
