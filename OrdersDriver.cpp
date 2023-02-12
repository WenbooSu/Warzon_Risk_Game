#include "Orders.h"
#include "OrdersDriver.h"

#include <string>
#include <iostream>

using namespace std;

string testOrders()
{
    OrdersList ol;

    Deploy dep("player1", false, "Map1");
    Advance adv("player1", false, "Map1", "Map2");
    Bomb bob("player1", false, "Map2");
    Blockade block("player1", false, "Map1");
    Airlift air("player1", false, "Map1", "Map3");
    Negotiate negot("player1", false, "player2");

    ol.display();

    ol.add(&dep);
    ol.add(&adv);
    ol.add(&bob);
    ol.add(&block);
    ol.add(&air);
    ol.add(&negot);
    //vector<Order*> new_ol = ol.getList();

    ol.remove(7);
    ol.remove(4);

    ol.move(0, 2);

    ol.display();

    negot.validate();
    negot.execute();
    return "OrdersDriver.cpp runs well, I guess?\n";
}

int main()
{   
    cout << testOrders();
    return 0;
}
