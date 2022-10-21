CC = g++
CFLAGS = -g -Wall -std=c++20

OBJS = main.o Alldiff.o Puzzle.o Sum.o

all: $(OBJS)
	$(CC) $(CFLAGS) -o p2 *.o 
	./p2

clean:
	rm ./p2
	rm *.o 

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

Alldiff.o: Alldiff.cpp Alldiff.h 
	$(CC) $(CFLAGS) -c Alldiff.cpp

Puzzle.o: Puzzle.cpp Puzzle.h 
	$(CC) $(CFLAGS) -c Puzzle.cpp

Sum.o: Sum.cpp Sum.h 
	$(CC) $(CFLAGS) -c Sum.cpp

