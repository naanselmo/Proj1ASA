all: botnet

botnet: Graph.o Person.o main.cpp
	g++ -O3 -ansi -Wall main.cpp Graph.o Person.o -lm

Graph.o: Graph.cpp Graph.hpp Person.o
	g++ -O3 -ansi -Wall -g -c Graph.cpp -lm

Person.o: Person.cpp Person.hpp
	g++ -O3 -ansi -Wall -g -c Person.cpp -lm

clean:
	rm *.o *.out
