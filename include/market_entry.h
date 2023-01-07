#pragma once

#include <iostream>
#include "item.h"

class MarketEntry
{
    Item* item;
    int price;

public:

    MarketEntry(Item* _item, int _price);

    Item* get_item() const;
    int get_price() const;
    void set_price(int new_price);

    friend std::ostream& operator <<(std::ostream& os, const MarketEntry& entry);
};