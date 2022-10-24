CC = g++
CFLAGS = -g -Wall -std=c++20

OBJS = main.o Alldiff.o BinaryArc.o Puzzle.o Sum.o Tile.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o p2 *.o 
	./p2

clean:
	rm ./p2
	rm *.o 

main.o: main.cpp Puzzle.h 
	$(CC) $(CFLAGS) -c main.cpp 

Alldiff.o: Alldiff.cpp Alldiff.h Tile.h macros.h 
	$(CC) $(CFLAGS) -c Alldiff.cpp

BinaryArc.o: BinaryArc.cpp 
	$(CC) $(CFLAGS) -c BinaryArc.cpp 

Puzzle.o: Puzzle.cpp Puzzle.h Alldiff.h BinaryArc.h Constraint.h Tile.h macros.h 
	$(CC) $(CFLAGS) -c Puzzle.cpp

Sum.o: Sum.cpp Sum.h 
	$(CC) $(CFLAGS) -c Sum.cpp

Tile.o: Tile.cpp Tile.h
	$(CC) $(CFLAGS) -c Tile.cpp