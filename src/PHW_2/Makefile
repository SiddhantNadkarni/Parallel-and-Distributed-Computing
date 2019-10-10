all: p1 p2

p1: p1.o
	g++ p1.o -o p1 -lpthread
p2: p2.o
	g++ p2.o -o p2 -lpthread

p1.o: p1.cpp
	g++ -std=c++11 -c p1.cpp 

p2.o: p2.cpp
	g++ -std=c++11 -c p2.cpp 
clean:
	rm *.o p1 p2 output.raw