#include "market.h"
#include "user.h"

using namespace std;

int main()
{
    Item ak("AK-47");
    Item awp("AWP");
    Item tec("Tec-9");

    Market market;

    User u1(1, "u1", 200, &market);
    User u2(2, "u2", 1300, &market);

    u1.add(ak, 0.5f, 34);
    u1.add(awp, 0.07f, 1);
    u2.add(tec, 0.99f, 69);

    vector<Item*> res = u1.find("AWP");

    if (!res.empty())
        u1.sell(res[0], 35);

    cout << market << endl;

    vector<MarketEntry*> res2 = market.find("AWP");

    if (!res2.empty())
        u2.buy(res2[0]);
}