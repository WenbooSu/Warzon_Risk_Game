#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Orders.h"
#include "Card.h"
#include "MapLoader.h"

using namespace std;

class Territory;    //Forward declaration of the class. The include for Mapload.h is in the cpp file for Player.
class PlayerStrategy;

class Player {
public:
    playerHand* hand;
    OrdersList* orderList;
    int armiesUsed;
    PlayerStrategy* ps; //NEW
    Map* THE_GAME_MAP; //NEW
    vector<int> armies_record; //NEW, to determine being attacked or not
    vector<Player*> players;
    Deck* deck;
    bool issueOrderDone;

    Player();
    Player(string, vector<Territory*>, playerHand*, OrdersList*);
    Player(string name, Map* map, playerHand* hand, OrdersList* ordersList);
    Player(const Player&); //copy constructor
    ~Player();

    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(Deck*, vector<Player*>, Map*);

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
    Territory* getTerritoryByName(vector<Territory*>, string);

    void setPlayerStrategy(PlayerStrategy* psp);
    Map* getMap();
    bool beingAttacked();

private:
    string name;
    vector<Territory*> territoryList;
    vector<Player*> noAttackList;
    int armies;
};

ostream& operator<<(ostream& os, Player player);
