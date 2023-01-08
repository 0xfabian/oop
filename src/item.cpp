#include "item.h"

std::ostream& operator <<(std::ostream& os, Item& item)
{
    if (item.type == ItemType::SKIN)
    {
        Skin& skin = dynamic_cast<Skin&>(item);

        os << skin;
    }
    else
        os << item.name;

    return os;
}

std::ostream& operator <<(std::ostream& os, Skin& skin)
{
    rlutil::saveDefaultColor();

    switch (skin.rarity)
    {
    case 1: rlutil::setColor(rlutil::LIGHTBLUE); break;
    case 2: rlutil::setColor(rlutil::MAGENTA); break;
    case 3: rlutil::setColor(rlutil::LIGHTMAGENTA); break;
    case 4: rlutil::setColor(rlutil::LIGHTRED); break;
    case 5: rlutil::setColor(rlutil::YELLOW); break;
    }

    os << skin.name;

    rlutil::resetColor();

    return os;
}