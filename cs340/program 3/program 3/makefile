all: puzzle

puzzle: main.o block.o puzzle.o snapshot.o
	g++ main.o block.o puzzle.o snapshot.o -o puzzle.out

main.o: main.cpp
	g++ -c main.cpp

block.o: block.cpp
	g++ -c block.cpp

puzzle.o: puzzle.cpp
	g++ -c puzzle.cpp

snapshot.o: snapshot.cpp
	g++ -c snapshot.cpp

clean:
	rm -rf *o puzzle
