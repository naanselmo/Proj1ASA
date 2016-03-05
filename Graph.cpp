#include <iostream>
#include "Graph.h"

Graph::Graph() {
    this->persons = nullptr;
    this->personsLength = 0;
}

void Graph::populate() {
    int linksLength;
    std::cin >> this->personsLength >> linksLength;
    this->persons = new Person *[personsLength];
    for (int i = 0; i < this->personsLength; i++) {
        this->persons[i] = new Person(i + 1);
    }
    for (int i = 0; i < linksLength; i++) {
        int from, to;
        std::cin >> from >> to;
        //Ids start at 1
        this->persons[--from]->addLink(this->persons[--to]);
    }
}

void Graph::print() {
    std::cout << "Persons: " << this->personsLength << std::endl;
    for (int i = 0; i < this->personsLength; ++i) {
        Person *person = this->persons[i];
        std::cout << "Person " << person->getId() << "[" << person << "] is linked to: " << std::endl;
        for (Person *link : person->getLinks()) {
            std::cout << "\t-> Person " << link->getId() << "[" << link << "]" << std::endl;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < this->personsLength; ++i) {
        delete this->persons[i];
    }
    delete[] this->persons;
}
