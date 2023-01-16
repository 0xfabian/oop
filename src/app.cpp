#include "app.h"

User* App::get_user(const std::string& name)
{
    for (const auto& user : users)
        if (user->get_name() == name)
            return user;

    return nullptr;
}

Item* App::get_item(const std::string& name)
{
    for (const auto& item : items)
        if (item->get_name() == name)
            return item;

    return nullptr;
}

bool App::register_user(const std::string& username)
{
    if (get_user(username))
        return false;

    users.push_back(new User(username, 0, &market));

    return true;
}

bool App::login(const std::string& username)
{
    User* user = get_user(username);

    if (user)
        active_user = user;
    else
        std::cout << "User does not exist\n";

    return user;
}

void App::logout()
{
    active_user = nullptr;
}

int App::load_items(const std::string& path)
{
    std::ifstream f(path);

    if (!f.is_open())
    {
        std::cout << "'" << path << "' was not found\n";
        return -1;
    }

    std::string line;
    int ret = 0;

    while (getline(f, line))
        if (add_item(line))
            ret++;

    return ret;
}

void App::add_item(Item* item)
{
    if (item)
        items.push_back(item);
}

bool App::add_item(const std::string& str)
{
    Item* item = Weapon::load(str, this);

    if (!item)
        item = Skin::load(str, this);

    if (!item)
        item = Case::load(str, this);

    add_item(item);

    return item;
}

bool App::give_item(const std::string& username, const std::string& name)
{
    User* u = get_user(username);

    if (!u)
    {
        std::cout << "User does not exist\n";
        return false;
    }

    Item* i = get_item(name);

    if (!i)
    {
        std::cout << "Item does not exist\n";
        return false;
    }

    u->add(i, true);

    return true;
}

void App::print_users()
{
    for (auto* const user : users)
        std::cout << *user << std::endl;
}

void App::print_items()
{
    for (auto* const item : items)
    {
        std::cout << *item;

        if (item->get_type() == ItemType::CASE)
            dynamic_cast<Case*>(item)->print_drops(std::cout << " ");

        std::cout << std::endl;
    }
}

App::~App()
{
    for (auto& user : users)
        delete user;

    for (auto& item : items)
        delete item;
}