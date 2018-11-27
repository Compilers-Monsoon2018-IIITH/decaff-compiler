%{

#include <bits/stdc++.h>
#include "ClassDefs.h"
#include "decaf.tab.h"
#define YY_DECL extern "C" int yylex()
	extern union Node yylval;
	using namespace std;
	int line_num = 0;
%}

Digit 				   [0-9]
Alpha                  [a-zA-Z]
Alpha_num              {Alpha}|{Digit}
ID                     {Alpha}{Alpha_num}*
character              (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])
char_literal  		   [']{character}[']
string_literal		   ["]{character}*["]


%%

"class"             {return CLASS;}
"Program"           {return PROGRAM;}
"void"              {return VOID;}
"callout"           {return CALLOUT;}
"int"				{yylval.stringVal = new std::string(yytext,yyleng); return INT;}
"boolean"			{yylval.stringVal = new std::string(yytext,yyleng); return BOOLEAN;}
"for"			    {return FOR;}
"break"			    {return BREAK;}
"continue"			{return CONTINUE;}
"if"			    {return IF;}
"else"			    {return ELSE;}
"return"			{return RETURN;}
"true"              {return true;}
"false"             {return false;}
[0-9][0-9]*			{yylval.integerVal = atoi(yytext); return decimal_literal;}
"0x"[0-9a-fA-F][0-9a-fA-F]* {yylval.integerVal = atoi(yytext); return hex_literal;}
{char_literal}		{yylval.stringVal = new std::string(yytext,yyleng);return char_literal;}
{string_literal}    {yylval.stringVal = new std::string(yytext,yyleng);return string_literal;}
{ID}                {yylval.stringVal = new std::string(yytext,yyleng);return ID;}
"+"					{return '+';}
"-"					{return '-';}
"*"					{return '*';}
"/"					{return '/';}
"("					{return '(';}
")"					{return ')';}
"%"					{return '%';}
"}"					{return '}';}
"{"					{return '{';}
">"					{return '>';}
"<"                 {return '<';}
"="					{return '=';}
"!"					{return '!';}
"&"					{return '&';}
"|"					{return '|';}
"["					{return '[';}
"]"					{return ']';}
";"                 {return ';';}
","					{return ',';}
"'"					{return '\'';}
"\""				{return '\"';}
[ \t]				{ }
\n		     		{++line_num;}
.					{ printf("Line No %d: Unrecognized Character\n", line_num	); }

%%

