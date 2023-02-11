

#include <vector>
#include <string>
#include Card.h
#include Orders.h


class Player
{
public: 
    Player();      
    Player(string name, vector<string*> territoryList, vector<Card*> hand,vector<Order*> orderList);
   
    Player(const Player&); //copy constructor

    void toDefend();
    void toAttack();
    void issueOrder(string territory);

    string getName();
    string getTerritory();
    vector<string*> getTerritoryList();
    vector<Hand*> getHand();
    vector<Order*> getOrderList();

    string setName();
    string setTerritory();
    vector<string*> setTerritoryList();
    vector<Hand*> setHand();
    vector<Order*> setOrderList();



private:
    string name;
    string territory;
    vector<string*> territoryList;
    vector<Card*> hand;
    vector<Order*> orderList;

}