/* $Id$ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include "ast.h"
#include "scanner.h"
#include "driver.h"

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start program

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="decaf"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

/*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

%union
{
	int integerVal;
	std::string* stringVal;
    class ASTnode* astnode;
    class ProgASTnode* progastnode;
    class DeclASTnode* declastnode;
    class FieldDeclsASTnode* fildeclsastnode;
    class FieldDeclASTnode* fildeclastnode;
    class VarstarASTnode* varstrastnode;
    class VarASTnode* varastnode;
    class IntLitASTnode* intlitastnode;
    class TypeASTnode* typeastnode;

}

%type <progastnode> program 
%type <declastnode> declaration
%type <fildeclsastnode> field_decls
%type <fildeclastnode> field_decl
%type <varstrastnode> variable_star
%type <varastnode> variable
%type <intlitastnode> int_literal
%type <typeastnode> TYPE


//%destructor { delete $$; } expr

 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%token END 0
%token EOL VOID
%token <integerVal> hex_literal decimal_literal 
%token <stringVal> ID char_literal TRUE FALSE PROGRAM
%token <stringVal> INT BOOLEAN IF FOR ELSE CLASS CALLOUT CONTINUE
%token <stringVal> RETURN BREAK string_literal	
%left '?'
%left '+' '-'
%left '*' '/'


%%

program : CLASS PROGRAM '{' declaration '}'  {$$ = new ProgASTnode($4); driver.ast.pRoot = $$;}
		;

declaration :field_decls method_decls {$$ = new DeclASTnode($1,$2); }
			;

field_decls : field_decl field_decls {$$ = $2 ; $$->push_back($1); }
			|  {$$ = new FieldDeclsASTnode();}
			;

		

field_decl : TYPE variable_star ';'{$$ = new FieldDeclASTnode($1,$2);}
		   ;

variable_star : variable {$$ = new VarstarASTnode(); $$->push_back($1); }
			  | variable ',' variable_star {$$ = $3 ; $$->push_back($1); }
			  ;

variable : ID {$$ = new VarASTnode(string("Normal"),*$1); }
		 | ID '[' int_literal ']' {$$ = new VarASTnode(string("Array"),*$1,$3);}
		 ;
		   		  	  


int_literal : decimal_literal {$$ = new IntLitASTnode(string("dec"),$1);}
			| hex_literal {$$ = new IntLitASTnode(string("hex"),$1);}
			;

TYPE : INT {$$ = new TypeASTnode(*$1);}
	 | BOOLEAN {$$ = new TypeASTnode(*$1);}
	 ;

%%

void decaf::Parser::error(const Parser::location_type& l,
			    		  const std::string& m)
{
    driver.error(l, m);
}
