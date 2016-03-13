all: botnet

botnet: graph.o person.o main.cpp
	g++ -O3 -ansi -Wall main.cpp graph.o person.o -lm

graph.o: graph.cpp graph.hpp person.o
	g++ -O3 -ansi -Wall -g -c graph.cpp -lm

person.o: person.cpp person.hpp
	g++ -O3 -ansi -Wall -g -c person.cpp -lm

clean:
	rm *.o *.out
