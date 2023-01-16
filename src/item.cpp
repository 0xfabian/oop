#include "item.h"
#include "app.h"

using namespace std;

void Skin::print(ostream& os) const
{
    // fix unused variables
    (void)weapon;
    (void)wear;
    (void)pattern;

    rlutil::saveDefaultColor();

    switch (rarity)
    {
    case 1: rlutil::setColor(rlutil::LIGHTBLUE);        break;
    case 2: rlutil::setColor(rlutil::MAGENTA);          break;
    case 3: rlutil::setColor(rlutil::LIGHTMAGENTA);     break;
    case 4: rlutil::setColor(rlutil::LIGHTRED);         break;
    case 5: rlutil::setColor(rlutil::YELLOW);           break;
    }

    os << name;

    rlutil::resetColor();
}

Item* Weapon::load(const string& str, App* app)
{
    vector<string> args = parse(str);

    if (args.size() == 1 && !app->get_item(str))
        return new Weapon(str);

    return nullptr;
}

Item* Skin::load(const string& str, App* app)
{
    vector<string> args = parse(str);

    if (args.size() == 3)
    {
        Weapon* weapon = dynamic_cast<Weapon*>(app->get_item(args[1]));

        if (weapon && !app->get_item(args[1] + " | " + args[0]))
        {
            int rarity;

            if (nxstoi(args[2], rarity))
                return new Skin(weapon, args[0], rarity);
        }
    }

    return nullptr;
}