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
* Human Player
*/
HumanPlayerStrategy::HumanPlayerStrategy(Player* player){
	this->player = player;
}


void HumanPlayerStrategy::issueOrder() {
	//Create a list of neighboring and your own territories to attack and defend.
	cout << "\n\nIt is now " << player->getName() << "'s turn." << endl;
	//Now issue deploy orders to the territories to defend for the remaining number of armies.
	int numDeploy;
	int availableArimes = player->getArmies() - player->armiesUsed;
	cout << "\nCurrent Player:\t" << player->getName() << endl;
	if (availableArimes > 0) {
		vector<Territory*> defendTerritories = this->toDefend();
		string terrioryName;
		Territory* territory = nullptr;
		cout << "Which territory to defend, or input end to stop: ";
		cin >> terrioryName;
		for (Territory* t : defendTerritories) {
			if (t->getTerritoryName() == terrioryName) {
				territory = t;
				break;
			}
		}
		cout << "Remaining armies: ";
		cout << availableArimes << endl;
		cout << "How many armies would you like to deploy: " << endl;
		cin >> numDeploy;
		//If more are ordered than available, set it to all available armies remaining.
		if (numDeploy > availableArimes) {
			numDeploy = availableArimes;
		}
		//When adding armies to defend your territory, a deploy order must be issued.
		player->orderList->add(new Deploy(this->player, false, numDeploy, territory));
		player->armiesUsed += numDeploy;
		cout << endl;
		cout << numDeploy << " armies are ordered to be deployed to " << territory->getTerritoryName() << endl;
	}
	else {
		//Commence issuing advance orders: moving armies between your own teritories, or issuing an attack
		//Or using cards in player's hand.
		vector<Territory*> attackTerritories = this->toAttack();
		vector<Territory*> defendTerritories = this->toDefend();
		cout << "Available Orders: " << endl;
		cout << "0 Advance Order" << endl;
		//From a list of the player's cards, execute one of the orders.
		cout << "Current cards : " << endl;
		player->getHand()->showHand();
		//Continue until a valid choice has been entered.
		int choice = -1;
		int numCards = player->getHand()->hand.size();
		while (choice < 0 || choice - 1 > numCards) {
			cout << "Choose an order based on its corresponding number." << endl;
			cin >> choice;
			if (choice == 0) {
				cout << "Advance Orders: " << endl;
				string baseTerritoryName;
				string targetTerritoryName;
				int armiesMoving = 0;
				cout << "Choose your territory to move armies from: ";
				cin >> baseTerritoryName;
				Territory* baseTerritory = player->getTerritoryByName(player->getTerritoryList(), baseTerritoryName);
				cout << "Choose a territory that belongs to enemy to attack or your own to defend: ";
				cin >> targetTerritoryName;
				//Check both the defend and the attack territories pointer list for the advanced order.
				Territory* adjacentTerritory = player->getTerritoryByName(attackTerritories, targetTerritoryName);
				if (adjacentTerritory == nullptr) {
					adjacentTerritory = player->getTerritoryByName(defendTerritories, targetTerritoryName);
				}
				cout << "How many armies would you like to move: ";
				cin >> armiesMoving;
				player->orderList->add(new Advance(this->player, false, armiesMoving, baseTerritory, adjacentTerritory));
				cout << "Continue issuing advance orders? Input end to stop." << endl;
			}
			else if (choice <= player->getHand()->hand.size() && player->getHand()->hand.size() > 0 && choice > 0) {
				Card card = player->getHand()->play(choice - 1, player->deck);
				//Based card name, issue the respective order, and give the correct respective input to issue the order.
				if (card.CardType == "airlift") {
					string sourceTerritory;
					string destinationTarget;
					int numArmies;
					cout << "What is the source territory to airlift from: ";
					cin >> sourceTerritory;
					cout << "What is the airlift destination: ";
					cin >> destinationTarget;
					cout << "How many armies would you like to arilift: ";
					cin >> numArmies;
					player->orderList->add(new Airlift(this->player, false, numArmies,
						player->getTerritoryByName(player->getTerritoryList(), sourceTerritory), player->getTerritoryByName(this->player->getTerritoryList(), destinationTarget)));
				}
				else if (card.CardType == "bomb") {
					string enemyTerritory;
					cout << "What enemy teritory would you like to target: ";
					cin >> enemyTerritory;
					player->orderList->add(new Bomb(this->player, false, player->getTerritoryByName(attackTerritories, enemyTerritory)));
				}
				else if (card.CardType == "blockade") {
					string playerTerritory;
					cout << "Which territory would you like to blockade: ";
					cin >> playerTerritory;
					player->orderList->add(new Blockade(this->player, false, player->getTerritoryByName(player->getTerritoryList(), playerTerritory)));
				}
				else if (card.CardType == "negotiate") {
					string enemyPlayerName;
					cout << "Which player would you like to negtoiate with: ";
					cin >> enemyPlayerName;
					Player* enemyPlayer = nullptr;
					for (Player* p : player->players) {
						if (p->getName() == enemyPlayerName) {
							enemyPlayer = p;
							break;
						}
					}
					player->orderList->add(new Negotiate(this->player, false, enemyPlayer));
				}
				cout << "\n" << endl;
			}
		}
	}
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    string terrioryName = "";
    vector<Territory*> defend;
    cout << "\nList of your territories to defend: " << endl;
    for (Territory* territory : player ->getTerritoryList()) {
		cout << territory->getTerritoryName() << "\t\tArmies: " << territory->getArmies() << endl;
        defend.push_back(territory);
    }
    return defend;
    return this->territories;
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    vector<Territory*> attack;
    cout << "\nList of territories to attack: " << endl;

    for (Territory* conquered : this->player->getTerritoryList())
    {
		int row = conquered->getTerritoryID() - 1;
        for (int j = 0; j < this->getPlayer()->getMap()->getMatrix()[row].size(); j++)
        {
            if (this->getPlayer()->getMap()->getMatrix()[row][j].getGraphWeight() == 1)
            {
				string territoryName = this->getPlayer()->getMap()->getMatrix()[row][j].getTerritoryName();
				bool ownsTerritory = false;
				for (Territory* t :  this->getPlayer()->getTerritoryList()) {
					if (territoryName == t->getTerritoryName()) {
						ownsTerritory = true;
						break;
					}
				}
				if (!ownsTerritory) {
					bool alreadyDisplayed = false;
					Territory* t = this->player->getTerritoryByName(this->player->THE_GAME_MAP->countries, territoryName);
					for (Territory* displayed : attack) {
						if (territoryName == displayed->getTerritoryName()) {
							alreadyDisplayed = true;
							break;
						}
					}
					if (!alreadyDisplayed) {
						attack.push_back(t);
						cout << this->getPlayer()->getMap()->getMatrix()[row][j].getTerritoryName() << "\t\tArmies: " <<
							this->getPlayer()->getMap()->getMatrix()[row][j].getArmies() << endl;
					}
				}
            }
        }
    }
    return attack;
}

/*
 * Aggressive Player
 */
AggressivePlayerStrategy::AggressivePlayerStrategy() = default;

vector<Territory*> AggressivePlayerStrategy::toAttack() {

    return this->territories;
}

vector<Territory*> AggressivePlayerStrategy::toDefend() {

    return this->territories;
}

void AggressivePlayerStrategy::issueOrder() {
    cout<<"TBC"<<endl;
}

/*
* Benevolent Player
*/

void BenevolentPlayerStrategy::issueOrder() {

}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {

    return this->territories;
}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {

    return this->territories;
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

vector<Territory*> NeutralPlayerStrategy::toDefend() {

    return this->territories;
}

vector<Territory*> NeutralPlayerStrategy::toAttack() {

    return this->territories;
}

/*
 * Cheater Player
 */
void CheaterPlayerStrategy::issueOrder() {
    cout<< "Cheater Player No Order"<<endl;
}

//Cheater player doesn't defend
vector<Territory*> CheaterPlayerStrategy::toDefend() {
   
    return this->territories;
}

/*
 * Cheater automatically conquers all territories that are adjacent from conquered territories
 */
vector<Territory*> CheaterPlayerStrategy::toAttack() {

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
    return all_territories;
}











