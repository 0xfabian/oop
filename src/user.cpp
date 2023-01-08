#include "user.h"
#include "market.h"

int User::id_max = 0;

void User::add(Item* item, bool clone)
{
    if (clone)
        item = item->clone();

    item->set_owner(this);

    inv.push_back(item);
}

void User::remove(Item* item)
{
    inv.remove(item);
}

std::vector<Item*> User::find(const std::string& item_name)
{
    bool find_all = (item_name == "");

    std::vector<Item*> result;

    for (auto* const item : inv)
        if (find_all || item->get_name().find(item_name) != std::string::npos)
            result.push_back(item);

    return result;
}

int User::buy(MarketEntry* entry)
{
    return market->do_transaction(this, entry);
}

void User::sell(Item* item, int price)
{
    market->list_item(item, price);
}

std::ostream& operator <<(std::ostream& os, const User& user)
{
    os << user.id << " " << user.name << " " << user.balance << "$";

    return os;
}

User:: ~User()
{
    for (auto& item : inv)
        delete item;
}