#include "market.h"
#include "user.h"

void Market::list_item(Item* item, int price)
{
    MarketEntry* me = new MarketEntry(item, price);

    entries.push_back(me);

    std::cout << item->get_owner()->get_name() << " listed " << item->get_name() << " for " << price << "$\n\n";
}

bool Market::do_transaction(User* buyer, MarketEntry* entry)
{
    int price = entry->get_price();

    if (buyer->get_balance() < price)
        return false;

    Item* item = entry->get_item();
    User* seller = item->get_owner();

    std::cout << buyer->get_name() << " bought " << item->get_name() << " from " << seller->get_name() << " for " << price << "$\n\n";

    seller->add_balance(price);
    buyer->add_balance(-price);

    seller->remove(item);
    buyer->add(item);

    entries.remove(entry);

    return true;
}

std::vector<MarketEntry*> Market::find(std::string name)
{
    std::vector<MarketEntry*> result;

    for (auto& entry : entries)
        if (entry->get_item()->get_name() == name)
            result.push_back(entry);

    return result;
}

std::ostream& operator <<(std::ostream& os, const Market& market)
{
    if (market.entries.empty())
    {
        os << "Market is empty\n";

        return os;
    }

    os << "Market:\n";

    for (auto& entry : market.entries)
        os << "    " << *entry << "\n";

    return os;
}

Market::~Market()
{
    for (auto& entry : entries)
        delete entry;
}