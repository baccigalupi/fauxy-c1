%{
	#include <stdio.h>
	#include "parser_state.h"
	#include "object.h"
	#include "parse.tab.h"

	#define ParseObject_wrap(T, S) *yylval = FxParseObject_create_bit(T, S); return T
%}

%option reentrant
%option noyywrap
%option header-file="lib/parser/lex.yy.h"
%option bison-bridge
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

[A-Z]+[A-Za-z0-9_\-]* 					{ ParseObject_wrap(TOKEN_CLASS_ID, yytext); }
-?[0-9]+\.[0-9]+          			{ ParseObject_wrap(TOKEN_FLOAT, yytext); }
-?[0-9]\.[0-9]+(e|E)-?[0-9]+  	{ ParseObject_wrap(TOKEN_FLOAT, yytext); }
-?[0-9]+                  			{ ParseObject_wrap(TOKEN_INTEGER, yytext); }
[\-<+&a-z0-9_]+[a-z0-9_\-]*[!?]? 	{ ParseObject_wrap(TOKEN_ID, yytext); }
:[a-z0-9_]+[a-z0-9_\-]* 		  	{ ParseObject_wrap(TOKEN_ATOM, yytext); }
\/.*\/[a-z]? 										{ ParseObject_wrap(TOKEN_REGEX, yytext); }
\"([^"]|\\.)*\"           			{ ParseObject_wrap(TOKEN_EVAL_STRING, yytext); }
\'([^']|\\.)*\'           			{ ParseObject_wrap(TOKEN_STRING, yytext); }

.                    						{ printf("unknown token: %s\n", yytext); }
