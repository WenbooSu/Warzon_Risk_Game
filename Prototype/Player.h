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
    Player(string name, vector<Territory*> territoryList, vector<Card*> hand,vector<Order*> orderList);
   
    Player(const Player&); //copy constructor

    void toDefend();
    void toAttack();
    void issueOrder(string territory);

    string getName();
    vector<Territory*> getTerritoryList();
    vector<Hand*> getHand();
    vector<Order*> getOrderList();

    string setName();
    vector<Territory*> setTerritoryList();
    vector<Hand*> setHand();
    vector<Order*> setOrderList();



private:
    string name;
    vector<Territory*> territoryList;
    vector<Card*> hand;
    vector<Order*> orderList;

}