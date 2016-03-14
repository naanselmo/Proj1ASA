#ifndef PERSON_H
#define PERSON_H

class Person {
    unsigned int id;

public:
    Person(unsigned int id);          // Constructor, creates a new person
    inline unsigned int getId() const;       // Returns a person's ID
    virtual ~Person();                // Deconstructor, cleans up a person
};

#endif //PERSON_H
