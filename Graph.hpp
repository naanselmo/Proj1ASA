#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <map>
#include <list>
#include <vector>
#include <limits>
#include "Person.hpp"

#define INFINITE std::numeric_limits<unsigned int>::max()

template<class T>
class Vertex {
public:
    T element;
    Vertex *parent;
    unsigned int visitedTime;
    unsigned int lowTime;
    unsigned int childrenCount;
    bool fundamental;
    std::list<Vertex *> neighbours;

public:
    Vertex(T element);

    void reset();

    void addLink(Vertex *vertex);

    std::list<Vertex *> &getNeighbours();

    virtual ~Vertex();
};

class Graph {
    Vertex<Person *> **vertex;
    unsigned int vertexLength;

public:
    Graph();

    void populate();

    void execute();

    void print();

    virtual ~Graph();

private:
    std::vector<Vertex<Person *> *> tarjan();

    void visit(Vertex<Person *> *vertex, unsigned int &time, std::vector<Vertex<Person *> *> &fundamentals);
};

#endif //GRAPH_H
