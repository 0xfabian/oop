#include "console.h"

using namespace std;

void cmd_register(App* app, const vector<string>& args)
{
    if (app->is_active_user())
        cout << "You need to log out first\n";
    else
    {
        if (args.size() == 2)
        {
            if (!app->register_user(args[1]))
                cout << "User already exists\n";
        }
        else
            print_use(args[0] + " username");
    }
}

void cmd_login(App* app, const vector<string>& args)
{
    if (args.size() == 2)
    {
        if (app->is_active_user())
        {
            if (app->get_active_user().get_name() == args[1])
                cout << "Already logged in\n";
            else
                cout << "You need to log out first\n";
        }
        else
            app->login(args[1]);
    }
    else
        print_use(args[0] + " username");
}

void cmd_logout(App* app, const vector<string>&)
{
    if (app->is_active_user())
    {
        Console::get_instance().clear_item_res();
        Console::get_instance().clear_market_res();

        app->logout();
    }
    else
        cout << "Already logged out\n";
}

void cmd_users(App* app, const vector<string>&)
{
    app->print_users();
}

void cmd_item(App* app, const vector<string>& args)
{
    bool failed = false;

    if (args.size() == 1)
        app->print_items();
    else if (args.size() == 2)
    {
        if (args[1] == "load")
        {
            int ret = app->load_items();

            if (ret >= 0)
                cout << "Loaded " << ret << " items\n";
        }
        else
            failed = true;
    }
    else
    {
        if (args[1] == "load")
        {
            for (auto i = 2ull; i < args.size(); i++)
            {
                int ret = app->load_items(args[i]);

                if (ret >= 0)
                {
                    if (args.size() > 3)
                        cout << args[i] << ": ";

                    cout << "loaded " << ret << " items\n";
                }
            }
        }
        else if (args[1] == "add")
        {
            for (auto i = 2ull; i < args.size(); i++)
                app->add_item(args[i]);
        }
        else if (args[1] == "give")
        {
            if (args.size() == 4)
                app->give_item(args[2], args[3]);
            else
                failed = true;
        }
        else
            failed = true;
    }

    if (failed)
        print_use("item\n     item load\n     item add name ...\n     item give user name");
}

void cmd_balance(App* app, const vector<string>& args)
{
    if (app->is_active_user())
    {
        if (args.size() == 1)
            cout << app->get_active_user().get_balance() << "$\n";
        else if (args.size() == 3 && args[1] == "add")
        {
            int amount;

            if (!nxstoi(args[2], amount) || amount < 1)
                print_error("invalid amount");
            else
                app->get_active_user().add_balance(amount);
        }
        else
            print_use(args[0] + "\n     " + args[0] + " add amount");
    }
    else
        cout << "You need to log in frist\n";
}

void cmd_inventory(App* app, const vector<string>& args)
{
    if (app->is_active_user())
    {
        std::string s = "";

        if (args.size() == 2)
            s = args[1];

        vector<Item*> item_res = app->get_active_user().find(s);

        Console::get_instance().set_item_res(item_res);

        if (item_res.empty())
            cout << "No items found\n";
        else
        {
            for (auto i = 0ull; i < item_res.size(); i++)
                cout << (i + 1) << ". " << *item_res[i] << endl;
        }
    }
    else
        cout << "You need to log in first\n";
}

void cmd_sell(App* app, const vector<string>& args)
{
    if (!app->is_active_user())
    {
        cout << "You need to log in first\n";
        return;
    }

    if (args.size() == 3)
    {
        const vector<Item*>& item_res = Console::get_instance().get_item_res();

        if (!item_res.empty())
        {
            int id;
            int price;

            if (!nxstoi(args[1], id) || id < 1 || id >(int)item_res.size())
                print_error("invalid index");
            else if (!nxstoi(args[2], price) || price < 0)
                print_error("invalid price");
            else
            {
                Item* ip = item_res[id - 1];
                app->get_active_user().sell(ip, price);
            }
        }
        else
            cout << "No result to choose from\n";
    }
    else
        print_use("sell id price");
}

void cmd_market(App* app, const vector<string>& args)
{
    string s = "";

    if (args.size() == 2)
        s = args[1];

    vector<MarketEntry*> market_res = app->get_market().find(s);

    if (app->is_active_user())
        Console::get_instance().set_market_res(market_res);

    if (market_res.empty())
        cout << "No market entries found\n";
    else
    {
        for (auto i = 0ull; i < market_res.size(); i++)
            cout << (i + 1) << ". " << *market_res[i] << endl;
    }
}

void cmd_buy(App* app, const vector<string>& args)
{
    if (!app->is_active_user())
    {
        cout << "You need to log in first\n";
        return;
    }

    if (args.size() == 2)
    {
        const vector<MarketEntry*>& market_res = Console::get_instance().get_market_res();

        if (!market_res.empty())
        {
            int id;

            if (!nxstoi(args[1], id) || id < 1 || id >(int)market_res.size())
                print_error("invalid index");
            else
            {
                MarketEntry* entry = market_res[id - 1];

                int ret = app->get_active_user().buy(entry);

                if (ret == 1)
                    cout << "Item already sold\n";
                else if (ret == 2)
                    cout << "Not enough money\n";
            }
        }
        else
            cout << "No result to choose from\n";
    }
    else
        print_use("buy id");
}

void cmd_clear(App*, const vector<string>&)
{
    rlutil::cls();
}

void cmd_quit(App*, const vector<string>&)
{
    Console::get_instance().quit();
}

Console::Console()
{
    rlutil::saveDefaultColor();

    commands["register"] = cmd_register;
    commands["r"] = cmd_register;
    commands["login"] = cmd_login;
    commands["logout"] = cmd_logout;
    commands["users"] = cmd_users;
    commands["u"] = cmd_users;
    commands["item"] = cmd_item;
    commands["balance"] = cmd_balance;
    commands["b"] = cmd_balance;
    commands["inventory"] = cmd_inventory;
    commands["inv"] = cmd_inventory;
    commands["sell"] = cmd_sell;
    commands["market"] = cmd_market;
    commands["m"] = cmd_market;
    commands["buy"] = cmd_buy;
    commands["clear"] = cmd_clear;
    commands["quit"] = cmd_quit;
    commands["q"] = cmd_quit;
}

void Console::run()
{
    while (!_quit)
    {
        if (app->is_active_user())
            cout << app->get_active_user().get_name() << " ";

        cout << "> ";

        auto& is = getline(cin, input);

        if (is.eof() || is.fail())
            break;

        args = parse(input);

        if (!args.empty())
        {
            if (commands.find(args[0]) != commands.end())
                commands[args[0]](app, args);
            else
                cout << "Unknown command\n";
        }
    }
}

vector<string> parse(const string& input)
{
    vector<string> ret;

    string word;
    bool in_word = false;
    bool in_quotes = false;

    for (const char& c : input)
    {
        if (isspace(c))
        {
            if (in_quotes)
            {
                in_word = true;
                word.push_back(c);
            }
            else if (in_word)
            {
                in_word = false;
                ret.push_back(word);
                word.clear();
            }
        }
        else
        {
            if (c == '"')
                in_quotes = !in_quotes;
            else
            {
                in_word = true;
                word.push_back(c);
            }
        }
    }

    if (in_word)
        ret.push_back(word);

    return ret;
}

void print_error(const string& str)
{
    rlutil::setColor(rlutil::LIGHTRED);
    cout << "error: ";

    rlutil::resetColor();
    cout << str << endl;
}

void print_use(const string& str)
{
    rlutil::setColor(rlutil::YELLOW);
    cout << "use: ";

    rlutil::resetColor();
    cout << str << endl;
}

bool nxstoi(const string& s, int& value) noexcept
{
    try
    {
        value = stoi(s);
    }
    catch (...)
    {
        return false;
    }

    return true;
}