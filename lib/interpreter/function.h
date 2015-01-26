#ifndef FxN_Class_h
#define FxN_Class_h 1

typedef struct FxN_Function {
  // arguments
  // expressions
} FxN_Function;

FxN_Class *FxN_Function_create(char *name, FxN_Class *super_class);
// arity
// arguments_match // given argument values, does it match
// arguments_signature_match // is this a duplicate method because the signature is identical

#endif

