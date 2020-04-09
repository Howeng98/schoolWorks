/* Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "y.tab.h"	/* header file generated by bison */
extern YYSTYPE yylval; //YYSTYPE
//extern int yylineno;
%}

/* Define regular expression label */
newline		[\n]
digit		[0-9]
letter		[a-zA-Z]
integer     {digit}+
double      {digit}+"."{digit}+
id			{letter}+({letter}|{digit})*

/*%option yylineno*/

%x COMMENT STRING_STATE

/* Rules section */
%%

 /* Arithmetic */
"+"     { return ADD; }
"-" 	{ return SUB; }
"*" 	{ return MUL; }
"/" 	{ return DIV; }
"%"     { return REMAIN; }
"++"    { return INCR; }
"--"    { return DECR; }

 /* Relational */
">"		{ return GREATER;}
"<"		{ return LESS; }
">="	{ return GREATER_EQUAL; }
"<="	{ return LESS_EQUAL; }
"=="	{ return EQUAL; }
"!="	{ return NEQUAL; }

 /* Assignment */
"="		{ return ASSIGN; }
"+="	{ return ADD_ASSIGN; }
"-="	{ return SUB_ASSIGN; }
"*="	{ return MUL_ASSIGN; }
"/="	{ return DIV_ASSIGN; }
"%="	{ return REMAIN_ASSIGN; }

 /* Logical */
"&&"	{ return AND; }
"||"	{ return OR; }
"!"		{ return NOT; }

 /* Delimiters */
"("		{ return LB; }
")"		{ return RB; }
"{"		{ return LCB; }
"}"		{ return RCB; }

 /* Print Keywords */
"print"		{ return PRINT; }
"println"	{ return PRINTLN; }

 /* Condition and Loop Keywords */
"if"		{ return IF; }
"else"		{ return ELSE; }
"for"		{ return FOR; }

 /* Declaration Keywords */
"var"		{ return VAR; }
"void"		{ return VOID; }
"int"		{ return INT; }
"float32"	{ return FLOAT; }

 /* String Constant */
\"				        { BEGIN STRING_STATE;}
<STRING_STATE>\"		{ BEGIN INITIAL;}
<STRING_STATE>[^"]*		{ strcpy(yylval.string, yytext); return STRING; }

 /* Number Constant */
{integer}	{ yylval.i_val = atoi(yytext); return I_CONST; }
{double}	{ yylval.f_val = atof(yytext); return F_CONST;}

 /* C type Comment */
"/*"				{ BEGIN COMMENT; }
<COMMENT>[^*\n]+	{ }
<COMMENT>\n			{ yylineno++; }
<COMMENT>"*"		{ }
<COMMENT>"*/"		{ BEGIN INITIAL; return COMMENTLINE; }

 /* C++ type Comment */
\/\/.*	{  return COMMENTLINE; }

 /* Variable ID */
 {id}       { strcpy(yylval.string, yytext); return ID; }

 /* others */

[\n]		{  return NEWLINE; }
[ \t]		{ } /* Ignore */
[^; \t] 	{ } /* Ignore other charactor sets */
<<EOF>>     { return 0; }

%%

int yywrap()
{
    return 1;
}