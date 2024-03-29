CC = g++
CFLAGS = -g -Wall -std=c++20

OBJS = main.o Alldiff.o BinaryArc.o Checker.o Constraint.o Control.o CSP.o Puzzle.o Sum.o Tile.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o p2 *.o 
	./p2
clean:
	rm ./p2
	rm *.o 

standard: $(OBJS)
	$(CC) $(CFLAGS) -o p2 *.o 
	./p2 1

overlap: $(OBJS)
	$(CC) $(CFLAGS) -o p2 *.o 
	./p2 2

killer: $(OBJS)
	$(CC) $(CFLAGS) -o p2 *.o 
	./p2 3

main.o: main.cpp Control.h 
	$(CC) $(CFLAGS) -c main.cpp 

Alldiff.o: Alldiff.cpp Alldiff.h Tile.h macros.h 
	$(CC) $(CFLAGS) -c Alldiff.cpp

BinaryArc.o: BinaryArc.cpp BinaryArc.h Tile.h 
	$(CC) $(CFLAGS) -c BinaryArc.cpp 

Checker.o: Checker.cpp Checker.h Puzzle.h Tile.h 
	$(CC) $(CFLAGS) -c Checker.cpp 

Constraint.o: Constraint.cpp Constraint.h 
	$(CC) $(CFLAGS) -c Constraint.cpp 

Control.o: Control.cpp Control.h Checker.h CSP.h Puzzle.h 
	$(CC) $(CFLAGS) -c Control.cpp 

CSP.o: CSP.cpp CSP.h Alldiff.h BinaryArc.h Constraint.h Puzzle.h Tile.h 
	$(CC) $(CFLAGS) -c CSP.cpp 

Puzzle.o: Puzzle.cpp Puzzle.h Alldiff.h BinaryArc.h Constraint.h Tile.h macros.h 
	$(CC) $(CFLAGS) -c Puzzle.cpp

Sum.o: Sum.cpp Sum.h 
	$(CC) $(CFLAGS) -c Sum.cpp

Tile.o: Tile.cpp Tile.h
	$(CC) $(CFLAGS) -c Tile.cpp