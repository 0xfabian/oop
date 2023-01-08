#include "market_entry.h"
#include "user.h"

std::ostream& operator <<(std::ostream& os, const MarketEntry& entry)
{
    Item* ip = entry.get_item();
    User* owner = ip->get_owner();

    os << *ip << "   " << entry.get_price() << "$    " << owner->get_name();

    return os;
}