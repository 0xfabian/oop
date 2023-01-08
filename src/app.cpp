#include "app.h"
#include "console.h"

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

Item* App::find_item(const std::string& name)
{
    for (const auto& item : items)
    {
        if (item->get_name() == name)
            return item;
    }

    return nullptr;
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
    std::vector<std::string> args;

    while (getline(f, line))
    {
        args = parse(line);

        if (!args.empty())
        {
            if (args.size() == 1)
            {
                if (add_item(args[0]))
                    ret++;
            }
            else if (args.size() == 3)
            {
                Item* item = find_item(args[1]);

                if (item && item->get_type() == ItemType::WEAPON)
                {
                    Weapon* weapon = dynamic_cast<Weapon*>(item);

                    if (!find_item(args[1] + " | " + args[0]))
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
    if (find_item(name))
        return false;

    items.push_back(new Weapon(name));

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

    Item* i = find_item(name);

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
    for (const auto& item : items)
        std::cout << *item << std::endl;
}

App::~App()
{
    for (auto& user : users)
        delete user;

    for (auto& item : items)
        delete item;
}