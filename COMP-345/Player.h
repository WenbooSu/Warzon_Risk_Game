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

    void toDefend(vector<string*>);
    void toAttack(vector<string*>);
    void issueOrder(string);

    string getName();
    vector<Territory*> getTerritoryList();
    playerHand getHand();//Hand class
    OrdersList getOrderList();//Orderlist class
    void noAttack(Player *ally);

    void setName(string);
    void setTerritoryList(vector<Territory*>);
    playerHand setHand();
    void addToHand(Card);
    OrdersList setOrderList();
    vector<Territory*> compareTerritoryList(vector<Territory*>, vector<Territory*>);
    int* getArmies();
    void addArmies(int);

private:
    string name;
    vector<Territory*> territoryList;
    vector<Player*> noAttackList;
    playerHand hand;
    OrdersList orderList;
    int* armies;
};

ostream& operator<<(ostream& os, Player player);
