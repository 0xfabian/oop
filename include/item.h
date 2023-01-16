#pragma once

#include <iostream>
#include <string>
#include <rlutil.h>
#include <vector>
#include <cstdlib>

#include "misc.h"

class User;
class App;

enum ItemType
{
    WEAPON,
    SKIN,
    CASE
};

class Item
{
    virtual void print(std::ostream& os) const { os << name; }

protected:

    User* owner = nullptr;

    ItemType type;
    std::string name;

public:

    Item(ItemType _type, const std::string& _name): type(_type), name(_name) {}

    virtual Item* clone() const = 0;

    virtual ~Item() = default;

    User* get_owner() const { return owner; }
    void set_owner(User* _owner) { owner = _owner; }

    std::string get_name() const { return name; }
    ItemType get_type() const { return type; }

    friend std::ostream& operator <<(std::ostream& os, const Item& item) { item.print(os); return os; }
};

class Weapon: public Item
{

public:

    explicit Weapon(const std::string& _name): Item(ItemType::WEAPON, _name) {}

    Item* clone() const override { return new Weapon(*this); }

    static Item* load(const std::string& str, App* app);
};

class Skin: public Item
{
    Weapon* weapon;

    std::string skin_name;
    int rarity;
    float wear = 0;
    int pattern = 0;

    void print(std::ostream& os) const override;

public:

    Skin(Weapon* _weapon, const std::string& _skin_name, int _rarity):
        Item(ItemType::SKIN, _weapon->get_name() + " | " + _skin_name),
        weapon(_weapon),
        skin_name(_skin_name),
        rarity(_rarity) {}

    Item* clone() const override { return new Skin(*this); }

    static Item* load(const std::string& str, App* app);
};

class Case: public Item
{
    std::vector<Skin*> drops;

public:

    Case(const std::string _name, std::vector<Skin*> _drops): Item(ItemType::CASE, _name + " Case"), drops(_drops) {}

    Item* clone() const override { return new Case(*this); }

    static Item* load(const std::string& str, App* app);

    void print_drops(std::ostream& os) const;

    void open() const;
};