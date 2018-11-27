# Compiler for Decaf language

Compiler to produce llvm IR for a given code in decaf language 

[**Decaf Syntax Specifications**]()

## Prerequisites

> llvm compiler installed
> Bison and Flex installed to work with C++

##Directory Structure
.
├── phase-1
│   ├── lex.yy.c
│   ├── Makefile
│   ├── parser
│   ├── parser.tab.c
│   ├── parser.tab.h
│   ├── parser.y
│   └── scanner.l
├── phase-2
│   ├── ast.cc
│   ├── ast.h
│   ├── calc.ll
│   ├── calc.yy
│   ├── driver.cc
│   ├── driver.h
│   ├── Makefile
│   ├── PostFixVisitor.h
│   └── scanner.h
├── phase-3
│   ├── a.out
│   ├── ClassDefs.h
│   ├── codegenerator.h
│   ├── decaf.l
│   ├── decaf.output
│   ├── decaf.tab.c
│   ├── decaf.tab.h
│   ├── decaf.y
│   ├── input.txt
│   ├── lex.yy.c
│   ├── Makefile
│   └── visitor.h
├── README
└── test-programs
    ├── binary.dcf
    ├── even.dcf
    ├── fact.dcf
    ├── fib.dcf
    ├── hanoi.dcf
    └── mergesort.dcf



## Usage

For phase-1
	Go to directory run make 
	parser executable is generated
	./parser <file> to test

For phase-2
	Go to directory and run make
	calc executable is generated
	./calc <file> to test	


Test files are in the folder **test-programs**

## Files

> Bison File: calc.yy

> Flex File: calc.ll

> AST Files: ast.h ast.cc

> Visitor Pattern: PostFixVisitor.h

> Driver Files: diver.cc driver.h

> Scanner Files: scanner.h

## Output

>ASt nodes of the program is generated

## Features
> This code has been tested on ubuntu. If this does not works with any other linux distro, try to check the installation process of bison, flex and llvm for that particular distro. Also Make file might not work with all the linux distros, so you need to change the linking part in the compilation process yourself.

> Can Parse Decaf syntax and 
> Can Create AST for any and all valid syntax of decaf language.


#Yet to do
>Generate IR for the code.