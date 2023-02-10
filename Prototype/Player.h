

#include <vector>
#include <string>
#include Card.h
#include Orders.h
using namespace std;

class Player
{
public: 
    Player();      
    Player(string name, vector<string*> territoryList, vector<Hand*> hand,vector<Order*> orderList);
   
    Player(const Player&); //copy constructor

    void toDefend();
    void toAttack();
    void issueOrder(string territory);

    string getName() const;
    vector<string*> getTerritory() const;
    vector<Hand*> getHand() const;
    vector<Order*> getOrder() const;

    string getName() const;
    vector<string*> setTerritory() const;
    vector<Hand*> setHand() const;
    vector<Order*> setOrder() const;

private
    string name;
    vector<string*> territoryList;
    vector<Hand*> hand;
    vector<Order*> orderList;

}