#include <vector>
#include <string>
#include<iostream>
#include MapLoader.h
#include Card.h
#include Orders.h
#include MapLoader.h
using namespace std;


class Player
{
public: 
    Player();      
    Player(string name, vector<Territory*> territoryList, vector<string*> hand,vector<string*> orderList);
   
    Player(const Player&); //copy constructor

    void toDefend();
    void toAttack();
    void issueOrder(string territory);

    string getName();
    vector<Territory*> getTerritoryList();
    vector<string*> getHand();//Hand class
    vector<string*> getOrderList();//Orderlist class

    string setName();
    vector<Territory*> setTerritoryList();
    vector<Hand*> setHand();
    vector<Order*> setOrderList();
};

ostream& operator<<(ostream& os, Player player);

private:
    string name;
    vector<Territory*> territoryList;
    vector<Card*> hand;
    vector<Order*> orderList;

}
class OrderTemp
{
    public:
    OrderTemp();
    OrderTemp(String title);
    OrderTemp(const OrderTemp&); //copy constructor
    String title;
};
