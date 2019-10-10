all: p1a p1b p2 prob21

p1a: p1a.o
	g++ p1a.o -o p1a

p1b: p1b.o
	g++ p1b.o -o p1b

p2: p2.o
	g++ p2.o -o p2

prob21: prob21.o
	g++ prob21.o -o prob21

p1a.o: p1a.cpp
	g++ -c src/HW_1/p1a.cpp

p1b.o: p1b.cpp
	g++ -c src/HW_1/p1b.cpp

p2.o: p2.cpp
	g++ -c src/HW_1/p2.cpp

prob21.o: prob21.cpp
	g++ -c src/HW_2/prob21.cpp

clean: 
	rm *.o p1a p1b p2 prob21 output.raw