%{
#include <stdio.h>	
%}

%token ID hex_literal decimal_literal char_literal arrayID true false string_literal method_call location Alpha Alpha_star digit_star
%left '+' '-'
%left '*' '/'

%%

expr   : location
	   | method_call
	   | literal
	   | expr bin_op expr
	   | '-' expr
	   | '!' expr
	   | '(' expr ')'
	   ;
	   


bin_op   : arth_op
		 | rel_op
		 | eq_op
		 | cond_op
		 ;

arth_op   : '+'
		  | '-'
		  | '*'
		  | '/'
		  | '%'
		  ;

rel_op   : '<'
		 | '>'
		 | '<''='
		 | '>''='
		 ;

eq_op   : '=''='
		| '!''='
		;

cond_op   : '&''&'
		  | '|''|'
		  ;


literal   : int_literal
		  | char_literal
		  | bool_literal
		  ;

		  				 		  		 

bool_literal : true
			 | false
			 ;

int_literal : decimal_literal
			| hex_literal
			;


%%

void main(int argc, char **argv)
{
	yyparse();
	printf("Parsing Over\n");
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}