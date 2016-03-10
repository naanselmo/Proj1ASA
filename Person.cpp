#include "Person.h"

Person::Person(unsigned int id) {
    this->id = id;
}

unsigned int Person::getId() {
    return this->id;
}

Person::~Person() {
}
