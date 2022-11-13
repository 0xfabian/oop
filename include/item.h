#pragma once

#include <iostream>
#include <string>

class User;

class Item
{
    User* owner;

    std::string name;
    float wear;
    int pattern;

public:

    Item(const std::string _name, float _wear = 0, int _pattern = 0);
    Item(const Item& item);
    Item& operator=(const Item& item);

    User* get_owner();
    void set_owner(User* _owner);

    std::string get_name();

    float get_wear();
    void set_wear(float _wear);

    int get_pattern();
    void set_pattern(int _pattern);

    friend std::ostream& operator <<(std::ostream& os, const Item& item);
};