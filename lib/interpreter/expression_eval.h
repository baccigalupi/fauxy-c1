#ifndef __expression_eval_h
#define __expression_eval_h

#include "../bricks/helpers.h"
#include "../parser/expressions.h"
#include "interpreter.h"
#include "object.h"

FxN_Object *fxi_evaluate(                   FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_literal(           FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_lookup(            FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_method(            FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_function(          FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_grouped(           FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_list(              FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_function_arguments(FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_method_arguments(  FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_local_assign(      FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_colon_expression(  FxI_Interpreter *interpreter, FxP_Expression *expression);
FxN_Object *fxi_evaluate_expressions(       FxI_Interpreter *interpreter, FxP_Expression *expression);

#endif
