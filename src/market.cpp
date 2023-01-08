#include "market.h"
#include "user.h"

void Market::list_item(Item* item, int price)
{
    for (const auto& entry : entries)
        if (entry->get_item() == item)
        {
            entry->set_price(price);
            return;
        }

    entries.push_back(new MarketEntry(item, price));
}

int Market::do_transaction(User* buyer, MarketEntry* entry)
{
    if (std::find(entries.begin(), entries.end(), entry) == entries.end())
        return 1;

    int price = entry->get_price();

    if (buyer->get_balance() < price)
        return 2;

    Item* item = entry->get_item();
    User* seller = item->get_owner();

    seller->add_balance(price);
    buyer->add_balance(-price);

    seller->remove(item);
    buyer->add(item);

    entries.remove(entry);

    delete entry;

    return 0;
}

std::vector<MarketEntry*> Market::find(const std::string& item_name)
{
    bool find_all = (item_name == "");

    std::vector<MarketEntry*> result;

    for (auto* const entry : entries)
        if (find_all || entry->get_item()->get_name().find(item_name) != std::string::npos)
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