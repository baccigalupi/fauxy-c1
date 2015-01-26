#ifndef FxN_Function_h
#define FxN_Function_h 1

typedef struct FxN_Function {
  int whatever;
} FxN_Function;

FxN_Function *FxN_Function_create(char *name, FxN_Class *super_class);
// arity
// arguments_match // given argument values, does it match
// arguments_signature_match // is this a duplicate method because the signature is identical

#endif
