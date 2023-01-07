#include "item.h"

class User;

Item& Item::operator=(const Item& item)
{
    this->owner = item.owner;
    this->type = item.type;
    this->name = item.name;

    return *this;
}

std::ostream& operator <<(std::ostream& os, const Item& item)
{
    os << item.name;

    return os;
}