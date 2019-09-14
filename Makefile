all: p1a p1b p2

p1a: p1a.o
	g++ p1a.o -o p1a

p1b: p1b.o
	g++ p1b.o -o p1b

p2: p2.o
	g++ p2.o -o p2

p1a.o: src/p1a.cpp
	g++ -c src/p1a.cpp

p1b.o: src/p1b.cpp
	g++ -c src/p1b.cpp

p2.o: src/p2.cpp
	g++ -c src/p2.cpp


clean: 
	rm *.o p1a p1b p2 output.raw