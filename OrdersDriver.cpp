#include "Orders.h"
#include "OrdersDriver.h"

#include <string>
#include <iostream>

using namespace std;

string testOrders()
{
    OrdersList ol;

    Order def_ord;
    Order ord("player1");
    Order ord_copy(ord);
    Deploy dep("player1", "Map1");
    Advance adv("player1", "Map1", "Map2");
    Bomb bob("player1", "Map2");
    Blockade block("player1", "Map1");
    Airlift air("player1", "Map1", "Map3");
    Negotiate negot("player1", "player2");

    //Order* ord_ptr = &def_ord;
    //ol.display();
    ol.add(&def_ord);
    //vector<Order*> new_ol = ol.getList();

    //cout << dep << endl;

    negot.execute();
   

    //Deploy dep;
    return "OrdersDriver.cpp runs well, I guess?";
}

int main()
{   
    cout << testOrders();
    return 0;
}
