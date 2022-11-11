#include "market.h"
#include "user.h"

using namespace std;

int main()
{
    Item ak("AK-47");
    Item awp("AWP");
    Item tec("Tec-9");

    Market market;

    User bozo(1, "bozo", 200, &market);
    User claut(2, "claut", 1300, &market);

    bozo.add(ak, 0.5f, 34);
    bozo.add(awp, 0.07f, 1);
    claut.add(tec, 0.99f, 69);

    vector<Item*> res = bozo.find("AWP");

    if (!res.empty())
        bozo.sell(res[0], 35);

    cout << market << endl;

    vector<MarketEntry*> res2 = market.find("AWP");

    if (!res2.empty())
        claut.buy(res2[0]);
}