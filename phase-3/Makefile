TARGET=mycomp
all=$(TARGET)
CC = g++
CFLAGS = -lfl
FLAGS=-w -Wno-deprecated -g -std=c++11
all: $(TARGET)
$(TARGET): lex.yy.c decaf.tab.c  ClassDefs.h codegenerator.h
	$(CC) $(FLAGS) lex.yy.c decaf.tab.c $(CFLAGS)
lex.yy.c: decaf.l
	flex decaf.l
decaf.tab.c: decaf.y
	bison -vd decaf.y
clean:
	rm *.c
veryclean:
	rm -f *.c decaf.tab.h a.out XML_* *.output