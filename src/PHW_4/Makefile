all: p1 p2_1 p2_2 p2_3

p1: p1.o
	mpicxx p1.o -o p1

p2_1: p2_1.o
	mpicxx p2_1.o -o p2_1

p2_2: p2_2.o
	mpicxx p2_2.o -o p2_2

p2_3: p2_3.o
	mpicxx p2_3.o -o p2_3

p1.o: p1.cpp
	mpicxx -c p1.cpp

p2_1.o: p2_1.cpp
	mpicxx -c p2_1.cpp

p2_2.o: p2_2.cpp
	mpicxx -c p2_2.cpp

p2_3.o: p2_3.cpp
	mpicxx -c p2_3.cpp


clean: 
	rm *.o p1 p2_1 p2_2 p2_3