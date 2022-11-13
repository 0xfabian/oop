#include "user.h"
#include "market.h"

User::User(int _id, const std::string _name, int _balance, Market* _market)
{
    id = _id;
    name = _name;
    balance = _balance;
    market = _market;

    std::cout << "User '" << name << "' has been added\n\n";
}

std::string User::get_name()
{
    return name;
}

int User::get_balance()
{
    return balance;
}

void User::set_balance(int amout)
{
    balance = amout;
}

void User::add_balance(int amout)
{
    balance += amout;
}

void User::add(const Item& item)
{
    Item* ip = new Item(item);

    add(ip);
}

void User::add(const Item& item, float wear, int pattern)
{
    Item* ip = new Item(item);

    ip->set_wear(wear);
    ip->set_pattern(pattern);

    add(ip);
}

void User::add(Item* item)
{
    item->set_owner(this);

    inv.push_back(item);

    std::cout << name << " recieved " << item->get_name() << "\n\n";
}

void User::remove(Item* item)
{
    inv.remove(item);
}

std::vector<Item*> User::find(const std::string item_name)
{
    std::vector<Item*> result;

    for (auto& item : inv)
        if (item->get_name() == item_name)
            result.push_back(item);

    return result;
}

bool User::buy(MarketEntry* entry)
{
    return market->do_transaction(this, entry);
}

void User::sell(Item* item, int price)
{
    market->list_item(item, price);
}

void User::show_inv()
{
    if (inv.empty())
        std::cout << name << " has no items\n";
    else
    {
        std::cout << name << ":\n";

        for (auto& item : inv)
            std::cout << "    " << *item << "\n";
    }
}

std::ostream& operator <<(std::ostream& os, const User& user)
{
    os << user.id << ", " << user.name << ", " << user.balance << "$";

    return os;
}

User:: ~User()
{
    for (auto& item : inv)
        delete item;
}