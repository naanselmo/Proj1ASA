#ifndef PERSON_H
#define PERSON_H

class Person {
    unsigned int id;

public:
    Person(unsigned int id);

    unsigned int getId();

    virtual ~Person();
};


#endif //PERSON_H
