#ifndef __structs_h
#define __structs_h 1

#include "../bricks/_bricks.h"

/*
 * There is an interdependency between struct members, and it is easier to have
 * these interconnected structs all in one file to avoid header hell.
 */

typedef struct FxI_Object {
  struct FxI_Object      *klass;
  FxB_HashMap            *attributes;
  void                   *value;
  // possible flags etc ...
  // int for ref count
  // int for closed/open
  // int for mark and sweep, and maybe don't mark for Class Object etc
} FxI_Object;

typedef FxB_HashMap FxI_NativeRegistry;

typedef struct FxI_Interpreter {
  // main event loop?
  // references to other loops
  FxB_List            *contexts; // stack of objects marking who is implicit self
  FxI_NativeRegistry  *registry;
} FxI_Interpreter;

typedef struct FxI_MethodGroup {
  char             *name;
  FxB_List         *functions; // this should change to methods
} FxI_MethodGroup;

typedef FxI_Object FxI_FunctionDefinition;

typedef FxI_Object FxI_MethodCallArguments;

typedef FxI_Object *(* FxI_NativeFunction)(FxI_Interpreter *interpreter, FxI_Object *self, FxI_MethodCallArguments *arguments);

#endif
