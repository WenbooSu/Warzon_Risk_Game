#include "PlayerStrategy.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void PlayerStrategy::setPlayer(Player * player) {
    this->player = player;
}

Player* PlayerStrategy::getPlayer()  {
    return this->player;
}

/*
 * Cheater Player
 */

/*
 * Cheater automatically conquers all territories that are adjacent from conquered territories
 */
Territory *CheaterPlayerStrategy::toAttack() {

    vector<Territory*> all_territories = this->getPlayer()->getTerritoryList();

    vector<Territory*> conquered_territories;
    for(int i=0; i<all_territories.size(); i++)
    {
        if (all_territories[i]->getPlayer()->getName() == this->getPlayer()->getName())
        {
            conquered_territories.push_back(all_territories[i]);
        }
    }
    for(int i=0; i<conquered_territories.size(); i++)
    {
        int row = conquered_territories[i]->getTerritoryID();
        for(int j=0; j<this->getPlayer()->getMap()->getMatrix().size(); j++)
        {
            if(this->getPlayer()->getMap()->getMatrix()[row][j].getGraphWeight() == 1)
            {
                if(this->getPlayer()->getMap()->getMatrix()[row][j].getPlayer()->getName() != this->getPlayer()->getName())
                {
                    this->getPlayer()->getMap()->getMatrix()[row][j].setPlayer(this->getPlayer());
                }
            }
        }
    }
    return nullptr;
}

//Cheater player doesn't defend
Territory * CheaterPlayerStrategy::toDefend() {
    return nullptr;
}

void CheaterPlayerStrategy::issueOrder() {
    cout<< "Cheater Player No Order"<<endl;
}

/*
 * Aggressive Player
 */
AggressivePlayerStrategy::AggressivePlayerStrategy() = default;

Territory* AggressivePlayerStrategy::toAttack() {
    return nullptr;
}

Territory* AggressivePlayerStrategy::toDefend() {
    return nullptr;
}

void AggressivePlayerStrategy::issueOrder() {
    cout<<"TBC"<<endl;
}

/*
 * Neutral Player
 */

NeutralPlayerStrategy::NeutralPlayerStrategy() = default;

void NeutralPlayerStrategy::issueOrder() {
    cout<< "Neutral Player No Order"<<endl;
}

void NeutralPlayerStrategy::changeStrategy()  {
    if(this->getPlayer()->beingAttacked())
    {
        this->getPlayer()->setPlayerStrategy(this);
    }
}

Territory* NeutralPlayerStrategy::toDefend() {

    return nullptr;
}

Territory* NeutralPlayerStrategy::toAttack() {

    return nullptr;
}











