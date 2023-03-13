#include <vector>
#include <string>
#include <iostream>
#include "Orders.h"

using namespace std;

class Player {
public:
    Player();
    Player(string, vector<string*>, vector<string*>, OrdersList);

    Player(const Player&); //copy constructor

    void toDefend(vector<string*>);
    void toAttack(vector<string*>);
    void issueOrder(string);

    string getName();
    vector<string*> getTerritoryList();
    vector<string*> getHand();//Hand class
    OrdersList getOrderList();//Orderlist class

    void setName(string);
    vector<string*> setTerritoryList();
    vector<string*> setHand();
    OrdersList setOrderList();
    vector<string*> compareTerritoryList(vector<string*>, vector<string*>);

private:
    string name;
    vector<string*> territoryList;
    vector<string*> hand;
    OrdersList orderList;

};

ostream& operator<<(ostream& os, Player player);