#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "item.h"

class MarketEntry;
class Market;

class User
{
    int id;
    std::string name;

    int balance;
    Market* market;

    std::list<Item*> inv;

public:

    User(int _id, std::string _name, int _balance, Market* _market);
    User(const User& user) = delete;
    User& operator=(const User& user) = delete;

    std::string get_name();

    int get_balance();
    void set_balance(int amout);
    void add_balance(int amout);

    void add(const Item& item);
    void add(const Item& item, float wear, int pattern);
    void add(Item* item);
    void remove(Item* item);

    std::vector<Item*> find(std::string name);

    bool buy(MarketEntry* entry);
    void sell(Item* item, int price);

    void show_inv();

    friend std::ostream& operator <<(std::ostream& os, const User& user);

    ~User();
};