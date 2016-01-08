#ifndef __structs_h
#define __structs_h 1

#include "../bricks/_bricks.h"

/*
 * There is an interdependency between struct members, and it is easier to have
 * these interconnected structs all in one file to avoid header hell.
 */

typedef struct FxI_Object {
  int                     type;
  struct FxI_Object      *scope;
  FxB_HashMap            *attributes;
  struct FxI_Interpreter *interpreter;
  void                   *value;
  Boolean                 closed; // double negative, but better defaults
} FxI_Object;

typedef FxB_HashMap FxI_NativeRegistry;

typedef struct FxI_Pool {
  FxB_HashMap *literals;
  FxB_HashMap *natives;
  FxB_List    *all;
  FxI_Object  *globals; // this needs to be an object so that all contexts are objects!
} FxI_Pool;

typedef struct FxI_Interpreter {
  // main event loop?
  // references to other loops
  FxI_Pool            *pool;
  FxB_List            *contexts;
  FxI_NativeRegistry  *registry;
} FxI_Interpreter;

typedef struct FxI_MethodGroup {
  char             *name;
  FxB_List         *functions;
} FxI_MethodGroup;

typedef FxI_Object FxI_FunctionDefinition;

typedef FxI_Object FxI_MethodCallArguments;
typedef FxI_Object *(* FxI_NativeFunction)(FxI_Interpreter *interpreter, FxI_MethodCallArguments *arguments);

#endif
