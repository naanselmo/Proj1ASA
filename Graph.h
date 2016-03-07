#ifndef GRAPH_H
#define GRAPH_H

#include <stack>
#include <map>
#include <list>
#include <vector>
#include "Person.h"

class Graph {
    Person **persons;
    unsigned int personsLength;

public:
    Graph();

    void populate();

    void execute();

    void print();

    virtual ~Graph();

private:
    std::vector<std::vector<Person *> > tarjan_execute();

    void tarjan_visit(Person *person, int &visited, std::map<Person *, int> &d, std::map<Person *, int> &low,
                      std::stack<Person *> &stack, std::map<Person *, bool> &stack_contains,
                      std::vector<std::vector<Person *> > &sccs);
};


#endif //GRAPH_H
