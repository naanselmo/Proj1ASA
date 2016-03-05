#ifndef PERSON_H
#define PERSON_H

#include <list>

class Person {
    int id;
    std::list<Person *> links;

public:
    Person(int id);

    void addLink(Person *person);

    std::list<Person *> &getLinks();

    int getId();

    virtual ~Person();
};


#endif //PERSON_H
