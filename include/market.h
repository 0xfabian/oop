#pragma once

#include <iostream>
#include <list>
#include <vector>

#include "item.h"

class MarketEntry
{
    Item* item;
    int price;

public:

    MarketEntry(Item* _item, int _price);

    Item* get_item() const;
    int get_price() const;

    friend std::ostream& operator <<(std::ostream& os, const MarketEntry& entry);
};

class Market
{
    std::list<MarketEntry*> entries;

public:

    Market() = default;
    Market(const Market& market) = delete;
    Market& operator=(const Market& market) = delete;

    void list_item(Item* item, int price);
    bool do_transaction(User* buyer, MarketEntry* entry);

    std::vector<MarketEntry*> find(std::string name);

    friend std::ostream& operator <<(std::ostream& os, const Market& market);

    ~Market();
};
