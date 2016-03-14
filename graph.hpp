#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <map>
#include <list>
#include <vector>
#include <limits>
#include "person.hpp"

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
    Vertex(T element);                                   // Constructor, creates a new vertex
    void reset();                                        // Resets a vertex to its initial state
    void addLink(Vertex* const vertex);                  // Connects the vertex with another one
    const std::list<Vertex *> &getNeighbours() const;    // Returns a list of vertices to which this vertex is connected
    virtual ~Vertex();                                   // Deconstructor, cleans up a vertex
};

class Graph {
    Vertex<Person *> **vertex;
    unsigned int vertexLength;

public:
    Graph();               // Constructor, creates a new graph
    void populate();       // Populates the graph with vertices
    void execute();        // Finds fundamental vertices, and prints them
    void print() const;    // Prints the graph
    virtual ~Graph();      // Deconstructor, cleans up a graph

private:
    std::vector<Vertex<Person *> *> findFundamentals();
    void visit(Vertex<Person *> *vertex, unsigned int &time, std::vector<Vertex<Person *> *> &fundamentals);
};

#endif //GRAPH_H
