all: facebook

facebook: Graph.o Person.o main.cpp
	g++ -std=c++11 -o facebook main.cpp Graph.o Person.o

Graph.o: Graph.cpp Graph.h Person.o
	g++ -std=c++11 -g -c Graph.cpp

Person.o: Person.cpp Person.h
	g++ -std=c++11 -g -c Person.cpp

clean:
	rm *.o facebook
