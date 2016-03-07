#include <iostream>
#include "Graph.h"

#define INFINITE -1

Graph::Graph() {
    this->persons = NULL;
    this->personsLength = 0;
}

void Graph::populate() {
    unsigned int linksLength;
    std::cin >> this->personsLength >> linksLength;
    this->persons = new Person *[personsLength];
    for (unsigned int i = 0; i < this->personsLength; i++) {
        this->persons[i] = new Person(i + 1);
    }
    for (unsigned int i = 0; i < linksLength; i++) {
        unsigned int from, to;
        std::cin >> from >> to;
        //Ids start at 1
        this->persons[--from]->addLink(this->persons[--to]);
    }
}

void Graph::execute() {
    std::vector<std::vector<Person *> > sccs = tarjan_execute();
    std::cout << "SCC found:\n";
    for (unsigned int i = 0; i < sccs.size(); i++) {
        std::vector<Person *> scc = sccs[i];
        std::cout << "{";
        for (unsigned int j = 0; j < scc.size(); j++) {
            std::cout << scc[j]->getId();
            if (j != scc.size() - 1) std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }
}

void Graph::print() {
    std::cout << "Persons: " << this->personsLength << std::endl;
    for (unsigned int i = 0; i < this->personsLength; i++) {
        Person *person = this->persons[i];
        std::cout << "Person " << person->getId() << "[" << person << "] is linked to: " << std::endl;
        std::list<Person *> links = person->getLinks();
        for (std::list<Person *>::iterator it = links.begin(); it != links.end(); it++) {
            Person *link = *it;
            std::cout << "\t-> Person " << link->getId() << "[" << link << "]" << std::endl;
        }
    }
}

Graph::~Graph() {
    for (unsigned int i = 0; i < this->personsLength; ++i) {
        delete this->persons[i];
    }
    delete[] this->persons;
}

std::vector<std::vector<Person *> > Graph::tarjan_execute() {
    int visited = 0;
    std::stack<Person *> stack;
    std::map<Person *, bool> stack_contains;
    std::map<Person *, int> d;
    std::map<Person *, int> low;

    for (unsigned int i = 0; i < this->personsLength; i++) {
        Person *person = this->persons[i];
        d[person] = INFINITE;
        stack_contains[person] = false;
    }

    std::vector<std::vector<Person *> > sccs;
    for (unsigned int i = 0; i < this->personsLength; i++) {
        Person *person = this->persons[i];
        if (d[person] == INFINITE) {
            this->tarjan_visit(person, visited, d, low, stack, stack_contains, sccs);
        }
    }
    return sccs;
}

void Graph::tarjan_visit(Person *person, int &visited, std::map<Person *, int> &d,
                         std::map<Person *, int> &low, std::stack<Person *> &stack,
                         std::map<Person *, bool> &stack_contains, std::vector<std::vector<Person *> > &sccs) {
    d[person] = low[person] = visited++;
    stack.push(person);
    stack_contains[person] = true;

    std::list<Person *> links = person->getLinks();
    for (std::list<Person *>::iterator current = links.begin(); current != links.end(); current++) {
        Person *link = *current;
        if (d[link] == INFINITE || stack_contains[link]) {
            if (d[link] == INFINITE)
                this->tarjan_visit(link, visited, d, low, stack, stack_contains, sccs);
            low[person] = std::min(low[person], low[link]);
        }
    }

    if (d[person] == low[person]) {
        std::vector<Person *> scc;
        Person *link = NULL;
        do {
            link = stack.top();
            stack.pop();
            stack_contains[link] = false;
            scc.push_back(link);
        } while (person != link);
        sccs.push_back(scc);
    }
}
