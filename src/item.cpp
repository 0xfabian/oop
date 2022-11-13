#include "item.h"

class User;

Item::Item(const std::string& _name, float _wear, int _pattern)
{
    owner = nullptr;
    name = _name;
    wear = _wear;
    pattern = _pattern;
}

Item::Item(const Item& item)
{
    owner = item.owner;
    name = item.name;
    wear = item.wear;
    pattern = item.pattern;
}

Item& Item::operator=(const Item& item)
{
    this->owner = item.owner;
    this->name = item.name;
    this->wear = item.wear;
    this->pattern = item.pattern;

    return *this;
}

User* Item::get_owner()
{
    return owner;
}

void Item::set_owner(User* _owner)
{
    owner = _owner;
}

std::string Item::get_name()
{
    return name;
}

float Item::get_wear()
{
    return wear;
}

void Item::set_wear(float _wear)
{
    wear = _wear;
}

int Item::get_pattern()
{
    return pattern;
}

void Item::set_pattern(int _pattern)
{
    pattern = _pattern;
}

std::ostream& operator <<(std::ostream& os, const Item& item)
{
    os << item.name << ", " << item.wear << ", " << item.pattern;

    return os;
}