#include "Order.h"
#include "OrdersDriver.h"

#include <string>
#include <iostream>

using namespace std;

string testOrders()
{
    //OrdersList ol;

    Order def_ord;
    Order ord("player1");
    Order ord_copy(ord);
    Deploy dep("player1", "Map1");
    Bomb bob("player1", "Map2");

    Order* ord_ptr = &def_ord;
    //ol.display();
    //ol.add(ord_ptr);
    //vector<Order*> new_ol = ol.getList();

    //cout << dep << endl;

    bob.execute();
   

    //Deploy dep;
    return "OrdersDriver.cpp runs well, I guess?";
}

int main()
{   
    cout << testOrders();
    return 0;
}