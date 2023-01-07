#pragma once

#include <iostream>
#include <string>

class User;

enum ItemType
{
    WEAPON,
    SKIN,
    CASE,
    KEY
};

class Item
{
    User* owner = nullptr;

    ItemType type;
    std::string name;

public:

    explicit Item(ItemType _type, const std::string& _name): type(_type), name(_name) {}
    Item(const Item& item): owner(item.owner), type(item.type), name(item.name) {}
    Item& operator=(const Item& item);

    User* get_owner() const { return owner; };
    void set_owner(User* _owner) { owner = _owner; };

    std::string get_name() const { return name; };
    ItemType get_type() const { return type; };

    friend std::ostream& operator <<(std::ostream& os, const Item& item);
};