#include "app.h"

bool App::register_user(const std::string& username)
{
    for (auto& user : users)
    {
        if (user->get_name() == username)
        {
            std::cout << "User already exists\n";
            return false;
        }
    }

    User* up = new User(username, 0, &market);

    users.push_back(up);

    return true;
}

bool App::login(const std::string& username)
{
    for (auto* const user : users)
    {
        if (user->get_name() == username)
        {
            active_user = user;
            return true;
        }
    }

    std::cout << "User does not exist\n";
    return false;
}

void App::logout()
{
    active_user = nullptr;
}

bool App::add_item(const std::string& name)
{
    for (auto& item : items)
    {
        if (item.get_name() == name)
        {
            std::cout << "Item '" << name << "' already exists\n";
            return false;
        }
    }

    items.push_back(Item(ItemType::WEAPON, name));

    return true;
}

bool App::give_item(const std::string& user, const std::string& name)
{
    User* u = nullptr;

    for (auto& _user : users)
    {
        if (_user->get_name() == user)
        {
            u = _user;
            break;
        }
    }

    if (!u)
    {
        std::cout << "User does not exist\n";
        return false;
    }

    Item* i = nullptr;

    for (auto& item : items)
    {
        if (item.get_name() == name)
        {
            i = &item;
            break;
        }
    }

    if (!i)
    {
        std::cout << "Item does not exist\n";
        return false;
    }

    u->add(*i);
    return true;
}

void App::print_users()
{
    for (auto* const user : users)
        std::cout << *user << std::endl;
}

void App::print_items()
{
    for (auto& item : items)
        std::cout << item.get_name() << std::endl;
}

App::~App()
{
    for (auto& user : users)
        delete user;
}