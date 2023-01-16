#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "item.h"

class Market;
class MarketEntry;

class User
{
    static int id_max;
    const int id;
    std::string name;

    int balance;
    Market* market;

    std::list<Item*> inv;

public:

    User(const std::string& _name, int _balance, Market* _market): id(id_max++), name(_name), balance(_balance), market(_market) {};
    User(const User& user) = delete;
    User& operator=(const User& user) = delete;

    std::string get_name() const { return name; }

    int get_balance() const { return balance; }
    //void set_balance(int amount) { balance = amount; }
    void add_balance(int amount) { balance += amount; }

    void add(Item* item, bool clone = false);
    void remove(Item* item);

    std::vector<Item*> find(const std::string& item_name);

    int buy(MarketEntry* entry);
    void sell(Item* item, int price);

    friend std::ostream& operator <<(std::ostream& os, const User& user);

    ~User();
};