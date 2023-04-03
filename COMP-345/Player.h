#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Orders.h"
#include "Card.h"
#include "MapLoader.h"

using namespace std;

class Territory;    //Forward declaration of the class. The include for Mapload.h is in the cpp file for Player.

class Player {
public:
    playerHand* hand;
    OrdersList* orderList;
    Player();
    Player(string, vector<Territory*>, playerHand*, OrdersList*);
    Player(const Player&); //copy constructor
    ~Player();

    vector<Territory*> toDefend();
    vector<Territory*> toAttack(vector<Territory*>);
    void issueOrder(Deck*, vector<Player*>, MapLoader*);

    string getName();
    vector<Territory*> getTerritoryList();
    playerHand* getHand();//Hand class
    OrdersList* getOrderList();//Orderlist class
    void noAttack(Player *ally);

    void setName(string);
    void setTerritoryList(vector<Territory*>);
    void addTerritory(Territory*);
    playerHand setHand();
    void addToHand(Card);
    void setOrderList(OrdersList*);
    vector<Territory*> compareTerritoryList(vector<Territory*>, vector<Territory*>);
    int getArmies();
    void addArmies(int);

private:
    string name;
    vector<Territory*> territoryList;
    vector<Player*> noAttackList;
    int armies;
    Territory* getTerritoryByName(vector<Territory*>, string);
};

ostream& operator<<(ostream& os, Player player);
