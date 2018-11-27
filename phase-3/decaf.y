%{
#include "visitor.h"
#include "ClassDefs.h"
#include <bits/stdc++.h>

  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern "C" int line_num;
  extern union Node yylval;
  void yyerror(const char *s);
  class ProgASTnode* start = NULL;
  int errors=0;
%}

%start program

%token END 0
%token EOL 
%token <integerVal> hex_literal decimal_literal 
%token TRUE RETURN BREAK FALSE  VOID
%token   IF FOR ELSE  CALLOUT CONTINUE
%token <stringVal> INT BOOLEAN PROGRAM CLASS ID char_literal string_literal	
%left '?'
%left '+' '-'
%left '*' '/'


%type <progastnode> program 
%type <declastnode> declaration
%type <fildeclsastnode> field_decls
%type <fildeclastnode> field_decl
%type <varstrastnode> variable_star
%type <varastnode> variable


%%
program : CLASS PROGRAM '{' declaration '}'  {$$ = new ProgASTnode($4); start=$$;}
		;

declaration : field_decls {$$ = new DeclASTnode($1); }
			;

field_decls : {$$ = new FieldDeclsASTnode();} 
			|field_decls field_decl {$$ = $1 ; $$->push_back($2); }			
			;		

field_decl : INT variable_star ';'{$$ = new FieldDeclASTnode(*$1,$2);}
		   | BOOLEAN variable_star ';'{$$ = new FieldDeclASTnode(*$1,$2);}
		   ;

variable_star : variable {$$ = new VarstarASTnode(); $$->push_back($1); }
			  | variable ',' variable_star {$$ = $3 ; $$->push_back($1); }
			  ;

variable : ID {$$ = new VarASTnode(string("Normal"),*$1); }
		 | ID '[' decimal_literal ']' {$$ = new VarASTnode(string("Array"),*$1,$3);}
		 ;



%%

int main(int argc, char **argv) {
  if(argc == 1) {
		printf("No Input File Given\n");
		exit(-1);
	}

	FILE *input = fopen(argv[1], "r");

	if (input == NULL){
		printf("Can't open the given file!\n");
		exit(-1);
	}
	yyin = input;
	yyparse();

	printf("Success\n");
	PostFixVisitor pfv;
	pfv.visit(*start);
}
void yyerror(const char *s){
	errors++;
	printf("Error:%s at %d\n",s,line_num);
  exit(-1);
}		 
