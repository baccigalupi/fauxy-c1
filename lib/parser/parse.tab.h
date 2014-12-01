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
     TOKEN_NIL = 260,
     TOKEN_ELIPSES = 261,
     TOKEN_DOT = 262,
     TOKEN_EQUAL_SIGN = 263,
     TOKEN_COLON = 264,
     TOKEN_SEMICOLON = 265,
     TOKEN_LINE_END = 266,
     TOKEN_COMMA = 267,
     TOKEN_STRING = 268,
     TOKEN_EVAL_STRING = 269,
     TOKEN_INTEGER = 270,
     TOKEN_FLOAT = 271,
     TOKEN_ATOM = 272,
     TOKEN_REGEX = 273,
     TOKEN_ID = 274,
     TOKEN_CLASS_ID = 275,
     TOKEN_DEFERRED_ARGUMENT = 276,
     TOKEN_BLOCK_DECLARATION = 277,
     TOKEN_OPEN_BRACE = 278,
     TOKEN_CLOSE_BRACE = 279,
     TOKEN_OPEN_PAREN = 280,
     TOKEN_CLOSE_PAREN = 281,
     TOKEN_NOT_OPERATOR = 282
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  FauxyBit  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LIB_PARSER_PARSE_TAB_H_INCLUDED  */
