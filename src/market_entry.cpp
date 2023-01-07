#include "market_entry.h"
#include "user.h"

MarketEntry::MarketEntry(Item* _item, int _price)
{
    item = _item;
    price = _price;
}

std::ostream& operator <<(std::ostream& os, const MarketEntry& entry)
{
    Item* ip = entry.get_item();
    User* owner = ip->get_owner();

    os << *ip << "   " << entry.get_price() << "$    " << owner->get_name();

    return os;
}