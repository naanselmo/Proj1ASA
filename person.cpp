#include "person.hpp"

inline Person::Person(unsigned int id)
{
    this->id = id;
}

inline unsigned int Person::getId() const
{
    return this->id;
}

inline Person::~Person()
{

}
