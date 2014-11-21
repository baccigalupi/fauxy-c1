#ifndef __bricks_number
#define __bricks_number

// TODO: change to max int size for machine and max float size
#define INT     int
#define A_TO_I  atoi
#define FLOAT   float
#define A_TO_F  atof

typedef enum {
  IntegerType,
  FloatType
} NumberType;

#define number_type(N)    ((N)->type)
#define number_value(N)   ((number_type(N) == IntegerType) ? ((N)->value.as_int) : ((N)->value.as_float))

typedef struct {
  int type;
  // TODO: change to pointer for right size per
  union {
    INT   as_int;
    FLOAT as_float;
  } value;
} Number;

Number *Number_create(const char *str);
void    number_destroy(Number *number);
void    number_convert(Number *number, int type);

#endif
