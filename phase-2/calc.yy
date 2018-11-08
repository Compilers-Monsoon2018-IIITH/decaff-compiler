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
    class MethDeclsASTnode* methdeclsastnode;
    class MethDeclASTnode* methdeclastnode;
    class MethodsASTnode* methodsastnode;
    class MethodASTnode* methodastnode;
    class BlockASTnode* blockastnode;
    class VarDeclsASTnode* vardeclsastnode;
    class VarDeclASTnode* vardeclastnode;
    class IdsASTnode* idsastnode;
    class StatstarASTnode* statstarastnode;
    class StatASTnode* statastnode;
    class LocationASTnode* locationastnode;
    class MethodCallASTnode* methcallastnode;
    class ExprPlusASTnode* exprplusastnode;
    class CallPlusASTnode* callplusastnode;
    class CallArgASTnode* callargastnode;
    class ExprASTnode* exprastnode;
    class LitASTnode* litastnode;
    class BoolLitASTnode* boollitastnode;
    class ArthOpASTnode* arthopastnode;
    class BinOpASTnode* binopastnode;
    class EqOpASTnode* eqopastnode;
    class RelOpASTnode* relopastnode;
    class CondOpASTnode* condopastnode;
}

%type <progastnode> program 
%type <declastnode> declaration
%type <fildeclsastnode> field_decls
%type <fildeclastnode> field_decl
%type <varstrastnode> variable_star
%type <varastnode> variable
%type <intlitastnode> int_literal
%type <typeastnode> TYPE
%type <methdeclsastnode> method_decls
%type <methdeclastnode> method_decl
%type <methodsastnode> methods
%type <methodastnode> method
%type <blockastnode> block
%type <vardeclsastnode> var_decls
%type <vardeclastnode> var_decl
%type <idsastnode> ids
%type <statstarastnode> statement_star
%type <statastnode> statement
%type <locationastnode> location
%type <methcallastnode> method_call
%type <callargastnode> callout_arg
%type <callplusastnode> callout_plus
%type <exprplusastnode> expr_plus
%type <exprastnode> expr
%type <litastnode> literal
%type <boollitastnode> bool_literal
%type <arthopastnode> arth_op
%type <binopastnode> bin_op
%type <relopastnode> rel_op
%type <condopastnode> cond_op
%type <eqopastnode> eq_op

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
%token EOL 
%token <integerVal> hex_literal decimal_literal 
%token <stringVal> ID char_literal TRUE FALSE PROGRAM VOID
%token <stringVal> INT BOOLEAN IF FOR ELSE CLASS CALLOUT CONTINUE
%token <stringVal> RETURN BREAK string_literal	
%left '?'
%left '+' '-'
%left '*' '/'


%%

program : CLASS PROGRAM '{' declaration '}'  {$$ = new ProgASTnode($4); driver.ast.pRoot = $$;}
		;

declaration : field_decls method_decls {$$ = new DeclASTnode($1,$2); }
			;

field_decls : {$$ = new FieldDeclsASTnode();} 
			|field_decls field_decl {$$ = $1 ; $$->push_back($2); }			
			;

method_decls : method_decl method_decls {$$ = $2 ; $$->push_back($1);}
			 | {$$ = new MethDeclsASTnode();}
			 ;			

field_decl : INT variable_star ';'{$$ = new FieldDeclASTnode(*$1,$2);}
		   | BOOLEAN variable_star ';'{$$ = new FieldDeclASTnode(*$1,$2);}
		   ;

variable_star : variable {$$ = new VarstarASTnode(); $$->push_back($1); }
			  | variable ',' variable_star {$$ = $3 ; $$->push_back($1); }
			  ;

variable : ID {$$ = new VarASTnode(string("Normal"),*$1); }
		 | ID '[' int_literal ']' {$$ = new VarASTnode(string("Array"),*$1,$3);}
		 ;

method_decl : VOID ID '(' methods ')' block {$$ = new MethDeclASTnode(*$1,*$2,$4,$6);}
			| INT ID '(' methods ')' block {$$ = new MethDeclASTnode(*$1,*$2,$4,$6);}
			| BOOLEAN ID '(' methods ')' block {$$ = new MethDeclASTnode(*$1,*$2,$4,$6);}
			;

methods : method {$$ = new MethodsASTnode(); $$->push_back($1);  }
		| method ',' methods {$$ = $3 ; $$->push_back($1); }
		;
method : INT ID {$$ = new MethodASTnode(*$1,*$2);}
	   | BOOLEAN ID {$$ = new MethodASTnode(*$1,*$2);}
	   ;							 

block : '{' var_decls statement_star '}' {$$ = new BlockASTnode($2,$3); }
	  ;

var_decls : var_decl var_decls {$$ = $2 ; $$->push_back($1); }
		  | {$$ = new VarDeclsASTnode(); }
		  ;

var_decl : INT ids ';' {$$ = new VarDeclASTnode(*$1,$2); }
		 | BOOLEAN ids ';' {$$ = new VarDeclASTnode(*$1,$2); }
		 ;

ids : ID {$$ = new IdsASTnode(); $$->push_back(*$1); }
	| ID ',' ids {$$ = $3 ; $$->push_back(*$1); }
	;		 

statement_star : statement statement_star {$$ = $2 ; $$->push_back($1); }
			   | {$$ = new StatstarASTnode(); }
			   ;

statement : location '=' expr ';' {$$ = new StatASTnode($1,$3); }
		  | location '+''=' expr ';' {$$ = new StatASTnode($1,$4); }
		  | location '-''=' expr ';' {$$ = new StatASTnode($1,$4); }
		  | method_call ';' {$$ = new StatASTnode($1); }
		  | IF '(' expr ')' block {$$ = new StatASTnode(*$1,$3,$5); }
		  | IF '(' expr ')' block ELSE block {$$ = new StatASTnode(*$1,*$6,$3,$7,$5); }
		  | FOR ID '=' expr ',' expr block {$$ = new StatASTnode(*$1,*$2,$4,$6,$7); }
		  | RETURN ';' {$$ = new StatASTnode(*$1); }
		  | RETURN expr ';' {$$ = new StatASTnode(*$1,$2); }
		  | BREAK ';' {$$ = new StatASTnode(*$1); }
		  | CONTINUE ';'{$$ = new StatASTnode(*$1); }
		  | block {$$ = new StatASTnode($1); }
		  ;
location : ID {$$ = new LocationASTnode(*$1);}
		 | ID '[' expr ']' {$$ = new LocationASTnode(*$1,$3);}
		 ;

method_call : ID '(' expr_plus ')' {$$ = new MethodCallASTnode(*$1,$3);}
			| CALLOUT '(' string_literal callout_plus ')'{$$ = new MethodCallASTnode(*$1,*$3,$4);}
			;

expr_plus : expr {$$ = new ExprPlusASTnode(); $$->push_back($1);}
		  | expr_plus ',' expr {$$=$1; $$->push_back($3);}	
		  ;

callout_plus : ',' callout_arg {$$=new CallPlusASTnode(); $$->push_back($2);}
			 | callout_plus ',' callout_arg {$$=$1;$$->push_back($3);}
			 ;

callout_arg : expr {$$ = new CallArgASTnode($1);}
			| string_literal {$$ = new CallArgASTnode(*$1);}
			;
expr : location {$$ = new ExprASTnode($1); }
	 | method_call{$$ = new ExprASTnode($1); }
	 | literal{$$ = new ExprASTnode($1); }
	 | expr bin_op expr {$$ = new ExprASTnode($1,$2,$3); }
	 | '-' expr{$$ = new ExprASTnode($2); }
	 | '!' expr{$$ = new ExprASTnode($2); }
	 | '(' expr ')'{$$ = new ExprASTnode($2); }
	 ;

literal   : int_literal {$$ = new LitASTnode($1); }
		  | char_literal {$$ = new LitASTnode(*$1); }
		  | bool_literal {$$ = new LitASTnode($1); }
		  ;	 						 		  		

bin_op   : arth_op {$$ = new BinOpASTnode($1); }
		 | rel_op {$$ = new BinOpASTnode($1); }
		 | eq_op {$$ = new BinOpASTnode($1); }
		 | cond_op {$$ = new BinOpASTnode($1); }
		 ;

arth_op   : '+'  {$$ = new ArthOpASTnode('+'); }
		  | '-'  {$$ = new ArthOpASTnode('-'); }
		  | '*'  {$$ = new ArthOpASTnode('*'); }
		  | '/'  {$$ = new ArthOpASTnode('/'); }
		  | '%'  {$$ = new ArthOpASTnode('%'); }
		  ;

rel_op   : '<'  {$$ = new RelOpASTnode('<'); }
		 | '>'  {$$ = new RelOpASTnode('>'); }
		 | '<''=' {$$ = new RelOpASTnode('<','='); }
		 | '>''=' {$$ = new RelOpASTnode('>','='); }
		 ;

eq_op   : '=''=' {$$ = new EqOpASTnode('=','='); }
		| '!''=' {$$ = new EqOpASTnode('!','='); }
		;		 		  

cond_op   : '&''&' {$$ = new CondOpASTnode('&','&'); }
		  | '|''|' {$$ = new CondOpASTnode('|','|'); }
		  ;

bool_literal : TRUE  {$$ = new BoolLitASTnode(*$1); }
			 | FALSE {$$ = new BoolLitASTnode(*$1); }
			 ;


int_literal : decimal_literal {$$ = new IntLitASTnode(string("dec"),$1);}
			| hex_literal {$$ = new IntLitASTnode(string("hex"),$1);}
			;



%%

void decaf::Parser::error(const Parser::location_type& l,
			    		  const std::string& m)
{
    driver.error(l, m);
}
