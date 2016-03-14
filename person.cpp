#include "person.hpp"

Person::Person(unsigned int id)
{
    this->id = id;
}

inline unsigned int Person::getId() const
{
    return this->id;
}

Person::~Person()
{

}
