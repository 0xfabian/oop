#pragma once

#include <iostream>
#include <string>
#include <rlutil.h>

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
protected:

    User* owner = nullptr;

    ItemType type;
    std::string name;

public:

    Item(ItemType _type, const std::string& _name): type(_type), name(_name) {}

    virtual Item* clone() const = 0;

    virtual ~Item() = default;

    User* get_owner() const { return owner; };
    void set_owner(User* _owner) { owner = _owner; };

    std::string get_name() const { return name; };
    ItemType get_type() const { return type; };

    friend std::ostream& operator <<(std::ostream& os, Item& item);
};

class Weapon: public Item
{

public:

    explicit Weapon(const std::string& _name): Item(ItemType::WEAPON, _name) {}

    Item* clone() const override { return new Weapon(*this); }
};

class Skin: public Item
{
    Weapon* weapon;

    std::string skin_name;
    int rarity;
    float wear = 0;
    int pattern = 0;

public:

    Skin(Weapon* _weapon, const std::string& _skin_name, int _rarity):
        Item(ItemType::SKIN, _weapon->get_name() + " | " + _skin_name),
        weapon(_weapon),
        skin_name(_skin_name),
        rarity(_rarity) {}

    Item* clone() const override { return new Skin(*this); }

    friend std::ostream& operator <<(std::ostream& os, Skin& skin);
};