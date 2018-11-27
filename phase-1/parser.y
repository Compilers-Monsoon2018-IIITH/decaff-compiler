%{
#include <stdio.h>
int yylex();
void yyerror(char * s );	
%}

%token ID hex_literal decimal_literal char_literal true false 
%token VOID INT BOOLEAN IF FOR ELSE class CALLOUT CONTINUE
%token RETURN BREAK string_literal 
%left '+' '-'
%left '*' '/'

%start program

%%
program : class ID '{' declaration '}'
		;

declaration : field_decls method_decls
			;		

field_decls : field_decls field_decl
			|
			;
method_decls : method_decl method_decls
			 |
			 ;			

field_decl : INT variable_star ';'
		   | BOOLEAN variable_star ';'
		   ;

variable_star : variable
			  | variable ',' variable_star
			  ;

variable : ID
		 | ID '[' int_literal ']'
		 ;

method_decl : INT ID '(' methods ')' block
			| VOID ID '(' methods ')' block
			| BOOLEAN ID '(' methods ')' block
			;


methods : method
		| method ',' methods
		;

method : INT ID
	   | BOOLEAN ID
	   ;


block : '{' var_decls statement_star '}'
	  ;

var_decls : var_decl var_decls
		  |
		  ;

statement_star : statement statement_star
		   	   |
		       ;

var_decl : INT ids ';'
		 | BOOLEAN ids ';'		  	  		
		 ;

ids : ID
	| ID ',' ids
	;


statement :location assign_op expr ';'
		  | method_call ';'
		  | IF '(' expr ')' block
		  | IF '(' expr ')' block ELSE block
		  | FOR ID '=' expr ',' expr block
		  | RETURN ';'
		  | RETURN expr ';'
		  | BREAK ';'
		  | CONTINUE ';'
		  | block
		  ;

assign_op : '='
		  | '+''='
		  | '-''='
		  ;

method_call : ID '(' expr_plus ')'
			| CALLOUT '(' string_literal callout_plus ')'
			;	


expr_plus : expr
		  | expr_plus ',' expr
		  ;

callout_plus : ',' callout_arg
		 	 | callout_plus ',' callout_arg
		 	 |
		 	 ;
location : ID
		 | ID '[' expr ']'
		 ;		 		 	 

callout_arg : expr
			| string_literal
			;



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

int main(int argc, char **argv)
{
	yyparse();
	printf("Parsing Over\n");
}

void yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}