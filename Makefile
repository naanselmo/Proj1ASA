all: botnet

botnet: Graph.o Person.o main.cpp
	g++ -O3 -ansi -Wall main.cpp Graph.o Person.o -lm

Graph.o: Graph.cpp Graph.h Person.o
	g++ -O3 -ansi -Wall -g -c Graph.cpp -lm

Person.o: Person.cpp Person.h
	g++ -O3 -ansi -Wall -g -c Person.cpp -lm

clean:
	rm *.o *.out
