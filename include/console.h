#pragma once

#include <rlutil.h>
#include <functional>
#include <unordered_map>

#include "app.h"
#include "misc.h"

class Console
{
    bool _quit = false;
    std::string input;
    std::vector<std::string> args;
    std::unordered_map<std::string, std::function<void(App*, const std::vector<std::string>&)>> commands;

    App* app = nullptr;
    std::vector<Item*> item_res;
    std::vector<MarketEntry*> market_res;

    Console();

public:

    static Console& get_instance()
    {
        static Console instace;

        return instace;
    }

    void link(App* _app) { app = _app; }
    void run();
    void quit() { _quit = true; }

    std::vector<Item*>& get_item_res() { return item_res; }
    void set_item_res(const std::vector<Item*>& _item_res) { item_res = _item_res; }

    std::vector<MarketEntry*>& get_market_res() { return market_res; }
    void set_market_res(const std::vector<MarketEntry*>& _market_res) { market_res = _market_res; }
};

void print_use(const std::string& str);
bool check_id(const std::string& str, int& id, size_t max);
bool check_price(const std::string& name, const std::string& str, int& value, int min = 0);