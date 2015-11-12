/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_LIB_PARSER_PARSE_TAB_H_INCLUDED
# define YY_YY_LIB_PARSER_PARSE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
     TOKEN_TRUE = 258,
     TOKEN_FALSE = 259,
     TOKEN_LOCAL_ASSIGN = 260,
     TOKEN_COLON = 261,
     TOKEN_EXPORT = 262,
     TOKEN_SEMICOLON = 263,
     TOKEN_LINE_END = 264,
     TOKEN_COMMA = 265,
     TOKEN_STRING = 266,
     TOKEN_EVAL_STRING = 267,
     TOKEN_INTEGER = 268,
     TOKEN_FLOAT = 269,
     TOKEN_SYMBOL = 270,
     TOKEN_REGEX = 271,
     TOKEN_ID = 272,
     TOKEN_CLASS_ID = 273,
     TOKEN_DEFERRED_ARGUMENT = 274,
     TOKEN_ELIPSES = 275,
     TOKEN_DOT = 276,
     TOKEN_FUNCTION_DECLARATION = 277,
     TOKEN_OPEN_BRACE = 278,
     TOKEN_CLOSE_BRACE = 279,
     TOKEN_OPEN_PAREN = 280,
     TOKEN_CLOSE_PAREN = 281,
     TOKEN_AND = 282,
     TOKEN_OR = 283,
     TOKEN_NOT = 284,
     TOKEN_EOF = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  void *  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (FxP_LexWrapper *state, FxP_ParserContext *context);

#endif /* !YY_YY_LIB_PARSER_PARSE_TAB_H_INCLUDED  */
