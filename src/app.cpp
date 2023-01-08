#include "app.h"
#include "console.h"

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
    int ret = 0;

    std::ifstream f(path);

    if (!f.is_open())
    {
        std::cout << "'" << path << "' was not found\n";
        return -1;
    }

    std::string line;

    while (getline(f, line))
    {
        std::vector<std::string> args = parse(line);

        if (!args.empty())
        {
            if (args.size() == 1)
            {
                if (add_item(args[0]))
                    ret++;
            }
            else if (args.size() == 3)
            {
                Item* item = get_item(args[1]);

                if (item && item->get_type() == ItemType::WEAPON)
                {
                    Weapon* weapon = dynamic_cast<Weapon*>(item);

                    if (!get_item(args[1] + " | " + args[0]))
                    {
                        int rarity;

                        if (nxstoi(args[2], rarity))
                        {
                            items.push_back(new Skin(weapon, args[0], rarity));
                            ret++;
                        }
                    }
                }
            }
        }
    }

    return ret;
}

bool App::add_item(const std::string& name)
{
    if (get_item(name))
        return false;

    items.push_back(new Weapon(name));

    return true;
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
        std::cout << *item << std::endl;
}

App::~App()
{
    for (auto& user : users)
        delete user;

    for (auto& item : items)
        delete item;
}