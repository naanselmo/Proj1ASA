#include <iostream>
#include "Person.h"

Person::Person(int id) {
    this->id = id;
    this->links = std::list<Person *>();
}

void Person::addLink(Person *person) {
    this->links.push_back(person);
}

std::list<Person *> &Person::getLinks() {
    return this->links;
}

int Person::getId() {
    return this->id;
}

Person::~Person() {
}
