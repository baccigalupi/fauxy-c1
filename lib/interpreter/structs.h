#ifndef __structs_h
#define __structs_h 1

#include "../bricks/_bricks.h"

/*
 * There is an interdependency between struct members, and it is easier to have
 * these interconnected structs all in one file to avoid header hell.
 */

typedef struct FxN_Object {
  int                     type;
  struct FxN_Object      *scope;
  FxB_HashMap            *attributes;
  struct FxI_Interpreter *interpreter;
  void                   *value;
  Boolean                 closed; // double negative, but better defaults
} FxN_Object;

typedef struct FxI_Pool {
  FxB_HashMap *literals;
  FxB_List    *all;
  FxN_Object  *globals; // this needs to be an object so that all contexts are objects!
} FxI_Pool;

typedef struct FxI_Interpreter {
  // main event loop?
  // references to other loops
  FxI_Pool *pool;
  FxB_List *contexts;
} FxI_Interpreter;

// not yet sure what this entails yet
typedef struct FxN_Function {
  int whatever;
} FxN_Function;

typedef struct FxN_MethodGroup {
  char             *name;
  FxB_List         *functions;
} FxN_MethodGroup;

#endif
