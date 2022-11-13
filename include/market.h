#pragma once

#include <iostream>
#include <list>
#include <vector>
#include "market_entry.h"

class Market
{
    std::list<MarketEntry*> entries;

public:

    Market() = default;
    Market(const Market& market) = delete;
    Market& operator=(const Market& market) = delete;

    void list_item(Item* item, int price);
    bool do_transaction(User* buyer, MarketEntry* entry);

    std::vector<MarketEntry*> find(const std::string& item_name);

    friend std::ostream& operator <<(std::ostream& os, const Market& market);

    ~Market();
};
