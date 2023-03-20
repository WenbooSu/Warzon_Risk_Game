#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Orders.h"
#include "Card.h"

using namespace std;

class Territory;    //Forward declaration of the class. The include for Mapload.h is in the cpp file for Player.

class Player {
public:
    Player();
    Player(string, vector<Territory*>, playerHand, OrdersList);
    Player(const Player&); //copy constructor
    ~Player();

    vector<Territory*> toDefend();
    vector<Territory*> toAttack(vector<Territory>);
    void issueOrder(Deck*, vector<Player*>, vector<Territory>);

    string getName();
    vector<Territory*> getTerritoryList();
    playerHand getHand();//Hand class
    OrdersList getOrderList();//Orderlist class

    void setName(string);
    void setTerritoryList(vector<Territory*>);
    void addTerritory(Territory*);
    playerHand setHand();
    void addToHand(Card);
    OrdersList setOrderList();
    vector<Territory*> compareTerritoryList(vector<Territory*>, vector<Territory*>);
    int* getArmies();
    void addArmies(int);

private:
    string name;
    vector<Territory*> territoryList;
    playerHand hand;
    OrdersList orderList;
    int* armies;
    Territory* getTerritoryByName(vector<Territory*>, string);
};

ostream& operator<<(ostream& os, Player player);