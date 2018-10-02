%{
#include "parser.tab.h"
int lineno = 0;
%}

Alpha                  [a-zA-Z]
Digit                  [0-9]
Alpha_num              {Alpha}|{Digit}
ID                     {Alpha}{Alpha_num}*


%%
[0-9][0-9]*			{return decimal_literal;}
"0x"[0-9a-fA-F][0-9a-fA-F]* {return hex_literal;}
"true"              {return true;}
"false"             {return false;}
"+"					{return '+';}
"-"					{return '-';}
"*"					{return '*';}
"/"					{return '/';}
"("					{return '(';}
")"					{return ')';}
">"					{return '>';}
"<"                 {return '<';}
"="					{printf("kjkdh");return '=';}
"!"					{return '!';}
"&"					{return '&';}
"|"					{return '|';}
"["					{return '[';}
"]"					{return ']';}
[\']				{return "'";}
[\"]				{return '"';}
[ \t]				{ }
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

