#include "person.hpp"

Person::Person(unsigned int id)
{
    this->id = id;
}

unsigned int Person::getId() const
{
    return this->id;
}

Person::~Person()
{

}
