#pragma once

#include <vector>

#include "market.h"
#include "item.h"
#include "user.h"

class App
{
    std::vector<Item> items;
    std::vector<User*> users;
    Market market;

    User* active_user = nullptr;

public:

    App() = default;

    bool is_active_user() { return active_user != nullptr; };
    User& get_active_user() { return *active_user; };
    Market& get_market() { return market; };

    bool register_user(const std::string& username);

    bool login(const std::string& username);
    void logout();

    bool add_item(const std::string& name);
    bool give_item(const std::string& user, const std::string& name);

    void print_users();
    void print_items();

    ~App();
};