#ifndef __expression_eval_h
#define __expression_eval_h

#include "../bricks/_bricks.h"
#include "../parser/_parser.h"
#include "../native/boolean_methods.h"

#include "interpreter.h"
#include "object.h"

#define NULL_OBJECT fxi_literal_get(interpreter, FALSE_KEY)

FxI_Object *fxi_evaluate(                               FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_literal(                       FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_lookup(                        FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_method(                        FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_function_definition(           FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_grouped(                       FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_list(                          FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_function_definition_arguments( FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_method_call_arguments(         FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_attr_assign(                   FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_colon_expression(              FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_assignment(                    FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_expressions(                   FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_import(                        FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_native(                        FxI_Interpreter *interpreter, FxP_Expression *expression);
FxI_Object *fxi_evaluate_parser(                        FxI_Interpreter *interpreter, FxP_ParserContext *context);

#endif
