#include <string>
#include "Player.h"

int main()
{
    vector<string*> territoryAll;
    vector<string*> territoryP1;
    vector<string*> territoryP2;
    string t1 = "Canada";
    string t2 = "USA";

    territoryAll.push_back(&t1);
    territoryAll.push_back(&t2);

    territoryP1.push_back(&t1);
    territoryP2.push_back(&t2);
    string b = "Bomb";
    string r = "Reinforcement";

    vector<string*> handP1;

    vector<string*> handP2;

    handP1.push_back(&b);
    handP2.push_back(&r);

    Order ot1 = Deploy();
    Order ot2 = Advance();
    Order ot3 = Bomb();
    Airlift ot4 = Airlift();

    OrdersList olP1;
    olP1.add(&ot1);
    olP1.add(&ot2);

    OrdersList olP2;
    olP1.add(&ot3);
    olP1.add(&ot4);

    string name1 = string("Yulong");
    string name2 = string("Zachary");

    Player p1 = Player(name1, territoryP1, handP1, olP1);
    Player p2 = Player(name2, territoryP2, handP2, olP2);

    cout << p1;
    cout << p2;

    p1.toAttack(p1.compareTerritoryList(territoryAll, p1.getTerritoryList()));
    p2.toAttack(p2.compareTerritoryList(territoryAll, p2.getTerritoryList()));

    p1.toDefend(p1.getTerritoryList());
    p2.toDefend(p2.getTerritoryList());

    p1.issueOrder("Deploy");
    p2.issueOrder("Airlift");
    return 0;
}