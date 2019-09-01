all: p1a p1b p2

p1a: p1a.o
	g++ p1a.o -o p1a

p1b: p1b.o
	g++ p1b.o -o p1b

p2: p2.o
	g++ p2.o -o p2

p1a.o: p1a.cpp
	g++ -c p1a.cpp

p1b.o: p1b.cpp
	g++ -c p1b.cpp

p2.o: p2.cpp
	g++ -c p2.cpp


clean: 
	rm *.o p1a p1b p2 output.raw