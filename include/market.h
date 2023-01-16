#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "market_entry.h"

class Market
{
    std::list<MarketEntry*> entries;

public:

    Market() = default;
    Market(const Market& market) = delete;
    Market& operator=(const Market& market) = delete;

    void list_item(Item* item, int price);
    bool cancel_item(Item* item);
    int do_transaction(User* buyer, MarketEntry* entry);

    std::vector<MarketEntry*> find(const std::string& item_name);
    MarketEntry* find(Item* item);

    friend std::ostream& operator <<(std::ostream& os, const Market& market);

    ~Market();
};
