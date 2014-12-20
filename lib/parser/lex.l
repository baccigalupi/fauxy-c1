%{
	#include <stdio.h>
	#include "parser_state.h"
	#include "../parser/bit.h"
	#include "parse.tab.h"

	#define T_VALUE(T_TYPE) *yylval = FauxyBit_create(T_TYPE, yytext); return T_TYPE
%}

%option reentrant
%option bison-bridge
%option noyywrap
%option header-file="lib/parser/lex.yy.h"
%option bison-locations

%%

"true"												{ return TOKEN_TRUE; }
"false"												{ return TOKEN_FALSE; }
"nil"													{ return TOKEN_NIL; }
"export"											{ return TOKEN_EXPORT; }
"and"													{ return TOKEN_AND; }
"&&"													{ return TOKEN_AND; }
"or"													{ return TOKEN_OR; }
"||"													{ return TOKEN_OR; }
"..."													{ return TOKEN_ELIPSES; }
".."													{ return TOKEN_ELIPSES; }
"."														{ return TOKEN_DOT; }
";"                         	{ return TOKEN_SEMICOLON; }
"("                         	{ return TOKEN_OPEN_PAREN; }
")"                         	{ return TOKEN_CLOSE_PAREN; }
","                         	{ return TOKEN_COMMA; }
"_"                         	{ return TOKEN_DEFERRED_ARGUMENT; }
"="                         	{ return TOKEN_EQUAL_SIGN; }
":"                         	{ return TOKEN_COLON; }
"->"                         	{ return TOKEN_BLOCK_DECLARATION; }
"{"                         	{ return TOKEN_OPEN_BRACE; }
"}"                         	{ return TOKEN_CLOSE_BRACE; }
"!"                         	{ return TOKEN_NOT; }
\/\*[^*]*\*\/             		{ /* comment, treat as white space */ }
\/\/[^\n]*                		{ /* comment, treat as white space */ }
[\n]                      		{ return TOKEN_LINE_END; }
[ \t]                     		{ /* white space, move along */ }

[A-Z]+[A-Za-z0-9_\-]* 					{ T_VALUE(TOKEN_CLASS_ID); }
-?[0-9]+\.[0-9]+          			{ T_VALUE(TOKEN_FLOAT); }
-?[0-9]\.[0-9]+(e|E)-?[0-9]+  	{ T_VALUE(TOKEN_FLOAT); }
-?[0-9]+                  			{ T_VALUE(TOKEN_INTEGER); }
[\-<+&a-z0-9_]+[a-z0-9_\-]*[!?]? 	{ T_VALUE(TOKEN_ID); }
:[a-z0-9_]+[a-z0-9_\-]* 		  	{ T_VALUE(TOKEN_ATOM); }
\/.*\/[a-z]? 										{ T_VALUE(TOKEN_REGEX); }
\"([^"]|\\.)*\"           			{ T_VALUE(TOKEN_EVAL_STRING); }
\'([^']|\\.)*\'           			{ T_VALUE(TOKEN_STRING); }

.                    						{ printf("unknown token: %s\n", yytext); }
