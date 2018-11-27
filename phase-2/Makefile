

CXX = g++
CXXFLAGS = -W -Wall -Wextra -ansi -g
INCLUDE = -I/usr/local/opt/flex/include/ -I./

all: calc

# generate parser and scanner
parser.cc: calc.yy
	bison -o parser.cc --defines=parser.h calc.yy

scanner.cc: calc.ll
	flex -o scanner.cc calc.ll


# Implicit rule to compile c++ files
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<


# Link executable
calc: parser.o scanner.o driver.o ast.o
	$(CXX) $(LDFLAGS) -o $@ parser.o scanner.o driver.o ast.o
	rm *.o

clean: 
	rm -rf parser.cc parser.h scanner.cc location.hh  position.hh stack.hh *.o calc
