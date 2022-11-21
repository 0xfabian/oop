#include "market.h"
#include "user.h"

void Market::list_item(Item* item, int price)
{
    MarketEntry* me = new MarketEntry(item, price);

    entries.push_back(me);
}

bool Market::do_transaction(User* buyer, MarketEntry* entry)
{
    int price = entry->get_price();

    if (buyer->get_balance() < price)
        return false;

    Item* item = entry->get_item();
    User* seller = item->get_owner();

    seller->add_balance(price);
    buyer->add_balance(-price);

    seller->remove(item);
    buyer->add(item);

    entries.remove(entry);

    delete entry;

    return true;
}

std::vector<MarketEntry*> Market::find(const std::string& item_name)
{
    bool find_all = (item_name == "");

    std::vector<MarketEntry*> result;

    for (auto* const entry : entries)
        if (find_all || entry->get_item()->get_name() == item_name)
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

    for (auto* const entry : market.entries)
        os << "    " << *entry << "\n";

    return os;
}

Market::~Market()
{
    for (auto& entry : entries)
        delete entry;
}