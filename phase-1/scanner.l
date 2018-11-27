%{
#include <stdio.h>	
#include "parser.tab.h"
extern int yylex();
int lineno = 0;
%}

Digit 				   [0-9]
Alpha                  [a-zA-Z]
Alpha_num              {Alpha}|{Digit}
ID                     {Alpha}{Alpha_num}*
character              (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])
char_literal  		   [']{character}[']
string_literal		   ["]{character}*["]


%%
"class"             {return class;}
"void"              {return VOID;}
"callout"           {return CALLOUT;}
"int"				{return INT;}
"boolean"			{return BOOLEAN;}
"for"			    {return FOR;}
"break"			    {return BREAK;}
"continue"			{return CONTINUE;}
"if"			    {return IF;}
"else"			    {return ELSE;}
"return"			{return RETURN;}
"true"              {return true;}
"false"             {return false;}
[0-9][0-9]*			{return decimal_literal;}
"0x"[0-9a-fA-F][0-9a-fA-F]* {return hex_literal;}
{char_literal}		{return char_literal;}
{string_literal}    {return string_literal;}
{ID}                {return ID;}
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
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

