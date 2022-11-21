#include "app.h"

using namespace std;

vector<string> parse(const string& input)
{
    vector<string> ret;

    string word;
    bool in_word = false;
    bool in_quotes = false;

    for (const char& c : input)
    {
        if (c == ' ')
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

int main()
{
    App app;

    string input;
    vector<string> arg;

    vector<Item*> item_res;
    vector<MarketEntry*> market_res;

    int last_command = 0;

    while (true)
    {
        if (app.is_active_user())
            cout << app.get_active_user().get_name() << " ";

        cout << "> ";

        getline(cin, input);

        arg = parse(input);

        int last_command_copy = last_command;
        last_command = 0;

        if (arg.size() > 0)
        {
            if (arg[0] == "register" || arg[0] == "r")
            {
                if (arg.size() == 2)
                    app.register_user(arg[1]);
                else
                    cout << "use: " << arg[0] << " username\n";
            }
            else if (arg[0] == "login")
            {
                if (arg.size() == 2)
                    app.login(arg[1]);
                else
                    cout << "use: " << arg[0] << " username\n";
            }
            else if (arg[0] == "logout")
            {
                app.logout();
            }
            else if (arg[0] == "users" || arg[0] == "u")
            {
                app.print_users();
            }
            else if (arg[0] == "item")
            {
                bool failed = false;

                if (arg.size() == 1)
                    app.print_items();
                else if (arg.size() == 2)
                    failed = true;
                else
                {
                    if (arg[1] == "add")
                    {
                        for (int i = 2; i < (int)arg.size(); i++)
                            app.add_item(arg[i]);
                    }
                    else if (arg[1] == "give")
                    {
                        if (arg.size() != 4)
                            failed = true;

                        app.give_item(arg[2], arg[3]);
                    }
                    else
                        failed = true;
                }

                if (failed)
                {
                    cout << "use: item\n";
                    cout << "     item add name\n";
                    cout << "     item give user name\n";
                }
            }
            else if (arg[0] == "inventory" || arg[0] == "inv")
            {
                if (app.is_active_user())
                {
                    string s = "";

                    if (arg.size() == 2)
                        s = arg[1];

                    item_res = app.get_active_user().find(s);

                    if (item_res.empty())
                        cout << "No items found\n";
                    else
                    {
                        last_command = 1;
                        for (int i = 0; i < (int)item_res.size(); i++)
                            cout << (i + 1) << ". " << item_res[i]->get_name() << endl;
                    }
                }
                else
                    cout << "You need to login\n";
            }
            else if (arg[0] == "balance" || arg[0] == "b")
            {
                if (app.is_active_user())
                {
                    if (arg.size() == 1)
                        cout << app.get_active_user().get_balance() << "$\n";
                    else if (arg.size() == 3 && arg[1] == "add")
                    {
                        int amount = stoi(arg[2]);

                        if (amount < 1)
                            cout << "Invalid amount\n";
                        else
                            app.get_active_user().add_balance(amount);
                    }
                    else
                    {
                        cout << "use: " << arg[0] << endl;
                        cout << "     " << arg[0] << " add amount\n";
                    }
                }
                else
                    cout << "You need to login\n";
            }
            else if (arg[0] == "sell")
            {
                if (last_command_copy == 1)
                    last_command = 1;

                if (arg.size() == 3)
                {
                    if (last_command_copy == 1)
                    {
                        int id = stoi(arg[1]) - 1;
                        int price = stoi(arg[2]);

                        if (id < 0 || id >= (int)item_res.size())
                            cout << "Invalid item index\n";
                        else if (price < 0)
                            cout << "Invalid price\n";
                        else
                        {
                            Item* ip = item_res[id];
                            app.get_active_user().sell(ip, price);
                        }
                    }
                    else
                        cout << "Use inventory command before sell\n";
                }
                else
                    cout << "use: sell id price\n";
            }
            else if (arg[0] == "market" || arg[0] == "m")
            {
                string s = "";

                if (arg.size() == 2)
                    s = arg[1];

                market_res = app.get_market().find(s);

                if (market_res.empty())
                    cout << "No market entries found\n";
                else
                {
                    last_command = 2;

                    for (int i = 0; i < (int)market_res.size(); i++)
                        cout << (i + 1) << ". " << *market_res[i] << endl;
                }
            }
            else if (arg[0] == "buy")
            {
                if (last_command_copy == 2)
                    last_command = 2;

                if (arg.size() == 2)
                {
                    if (last_command_copy == 2)
                    {
                        int id = stoi(arg[1]) - 1;

                        if (id < 0 || id >= (int)market_res.size())
                            cout << "Invalid market entry index\n";
                        else
                        {
                            MarketEntry* entry = market_res[id];

                            if (!app.get_active_user().buy(entry))
                                cout << "Not enough money\n";
                        }
                    }
                    else
                        cout << "Use market command before buy\n";
                }
                else
                    cout << "use: buy id\n";
            }
            else
                cout << "Unknown command\n";
        }
    }
}