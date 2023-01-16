#pragma once

#include <iostream>
#include "item.h"

class MarketEntry
{
    Item* item;
    int price;

public:

    MarketEntry(Item* _item, int _price): item(_item), price(_price) {}

    Item* get_item() const { return item; }
    int get_price() const { return price; }
    void set_price(int new_price) { price = new_price; }

    friend std::ostream& operator <<(std::ostream& os, const MarketEntry& entry);
};