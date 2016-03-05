#ifndef GRAPH_H
#define GRAPH_H

#include "Person.h"

class Graph {
    Person **persons;
    int personsLength;

public:
    Graph();

    void populate();

    void print();

    virtual ~Graph();
};


#endif //GRAPH_H
