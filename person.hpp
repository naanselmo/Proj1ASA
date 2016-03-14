#ifndef PERSON_H
#define PERSON_H

class Person {
    unsigned int id;

public:
    inline Person(unsigned int id);          // Constructor, creates a new person
    inline unsigned int getId() const;       // Returns a person's ID
    inline virtual ~Person();                // Deconstructor, cleans up a person
};

#endif //PERSON_H
