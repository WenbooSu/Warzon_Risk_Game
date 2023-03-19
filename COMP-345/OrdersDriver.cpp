#include "Orders.h"
#include <string>
#include <iostream>

using namespace std;

string testOrders()
{
    OrdersList ol;

    //Order def_ord;
    //Order ord("player1");
    Deploy dep("player1", false, "Map1");
    Advance adv("player1", false, "Map1", "Map2");
    Bomb bob("player1", false, "Map2");
    Blockade block("player1", false, "Map1");
    Airlift air("player1", false, "Map1", "Map1");
    Negotiate negot("player1", false, "player2");

    ol.display();

    ol.add(&dep);
    ol.add(&adv);
    ol.add(&bob);
    ol.add(&block);
    ol.add(&air);
    ol.add(&negot);

    ol.remove(7);
    ol.remove(4);

    ol.move(0, 2);

    ol.display();
    
    dep.validate();
    dep.execute();

    adv.validate();
    adv.execute();
    
    bob.validate();
    bob.execute();

    block.validate();
    block.execute();
    
    air.validate();
    air.execute();
    
    negot.validate();
    negot.execute();

    return "OrdersDriver.cpp runs well\n";
}

int driver()
{   
    cout << testOrders();
    return 0;
}
