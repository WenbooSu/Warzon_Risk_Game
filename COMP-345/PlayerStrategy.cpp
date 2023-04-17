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
	string endDecision = "end";
	string decision;
	cout << "\nPlayer: " << player->getName() << ", conitnue issuing orders afterwards? Type " << endDecision << " to stop: " << endl;
	cin >> decision;
	if (decision == endDecision) {
		this->player->issueOrderDone = true;
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
    for (Territory* conquered : this->player->getTerritoryList()){
		int row = conquered->getTerritoryID() - 1;
        for (int j = 0; j < this->getPlayer()->getMap()->getMatrix()[row].size(); j++) {
            if (this->getPlayer()->getMap()->getMatrix()[row][j].getGraphWeight() == 1) {
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
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) {
	this->player = player;
}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> attack;
	//Get the teritory with the strongest army.
	Territory* strongestTerritory = this->player->getTerritoryList()[0];
	for (Territory* t : this->player->getTerritoryList()) {
		if (t->getArmies() >= strongestTerritory->getArmies()) {
			strongestTerritory = t;
		}
	}
	//Attack the first enemy territory that the payer's strongest army can find.
	int row = strongestTerritory->getTerritoryID() - 1;
	for (int j = 0; j < this->getPlayer()->getMap()->getMatrix()[row].size(); j++) {
		if (this->getPlayer()->getMap()->getMatrix()[row][j].getGraphWeight() == 1) {
			string territoryName = this->getPlayer()->getMap()->getMatrix()[row][j].getTerritoryName();
			bool ownsTerritory = false;
			for (Territory* t : this->getPlayer()->getTerritoryList()) {
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
				}
			}
		}
		}
	return attack;
}

vector<Territory*> AggressivePlayerStrategy::toDefend() {
	string terrioryName = "";
	vector<Territory*> defend;
	for (Territory* territory : player->getTerritoryList()) {
		cout << territory->getTerritoryName() << "\t\tArmies: " << territory->getArmies() << endl;
		defend.push_back(territory);
	}
	return defend;
}

void AggressivePlayerStrategy::issueOrder() {
	int availableArimes = player->getArmies() - player->armiesUsed;
	if (availableArimes > 0) {
		//Begin by creating a deploy order, deplyong all armies on the strongest territory.
		vector<Territory*> defendList = this->toDefend();
		vector<Territory*> attackList = this->toAttack();
		Territory* defend = defendList[0];
		for (Territory* t : defendList) {
			if (t->getArmies() >= defend->getArmies()) {
				defend = t;
			}
		}
		player->orderList->add(new Deploy(this->player, false, this->player->getArmies(), defend));
		player->armiesUsed += this->player->getArmies();
		cout << this->player->getName() << " has aggresively deployed all their armies, " << this->player->getArmies() << ", on " << defend->getTerritoryName() << "." << endl;
	}
	else {
		//After deploying all armies, keep advancing until they can't, using the strongest armies available.
		//Get the strongest territory.
		Territory* strongestTerritory = this->player->getTerritoryList()[0];
		for (Territory* t : this->player->getTerritoryList()) {
			if (t->getArmies() >= strongestTerritory->getArmies()) {
				strongestTerritory = t;
			}
		}
		//Find adjacent territories for the strongest territory to attack.
		vector<Territory*> attackList = this->toAttack();
		//Attack the first territory it can find, otherwise, it ends its turn.
		if (attackList.size() > 0) {
			this->player->orderList->add(new Advance(this->player, false, strongestTerritory->getArmies(), strongestTerritory, attackList[0]));
		}
		this->player->issueOrderDone = true;
	}
}

/*
* Benevolent Player
*/

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) {
	this->player = player;
}

void BenevolentPlayerStrategy::issueOrder() {
	//Get a list of all the territories with the least amount of armies deployed to it.
	vector<Territory*> defend = this->toDefend();
	//Go about equally distributing remaining armies to weakest territories until there are none.
	int armiesEqualDistribute = this->player->getArmies() / defend.size();
	if (armiesEqualDistribute <= 0) {
		armiesEqualDistribute = 1;
	}
	//Issue deploy orders to as many of the player's weakest territories as possible.
	for (Territory* territory : defend) {
		player->orderList->add(new Deploy(this->player, false, armiesEqualDistribute, territory));
		cout << this->player->getName() << " has benevolently deployed " << armiesEqualDistribute << ", armies to defend " <<territory->getTerritoryName() << "." << endl;
		player->armiesUsed += armiesEqualDistribute;
		if (this->player->armiesUsed >= this->player->getArmies()) {
			break;
		}
	}
	this->player->issueOrderDone = true;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> defend;
    //Find the smallest amount of armies deployed to a territory.
	int smallest = this->player->getTerritoryList()[0]->getArmies();
	for (Territory* territory : this->player->getTerritoryList()) {
		if (territory->getArmies() < smallest) {
			smallest = territory->getArmies();
		}
	}
	//Now create a list of all the territories with the smallest amount of armies deployed.
	for (Territory* territory : this->player->getTerritoryList()) {
		if (territory->getArmies() == smallest) {
			defend.push_back(territory);
		}
	}
	return defend;
}

vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	//Benevolent player does not attack, therefore, it will return its own territories.
    return this->territories;
}

/*
 * Neutral Player
 */

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
	this->player = player;
}

void NeutralPlayerStrategy::issueOrder() {
    cout<< "Neutral Player No Order"<<endl;
	this->player->issueOrderDone = true;
}

void NeutralPlayerStrategy::changeStrategy()  {
	//If a neutral player is attack, change its strategy to aggressive.
    if(this->getPlayer()->beingAttacked())
    {
        this->getPlayer()->setPlayerStrategy(new AggressivePlayerStrategy(this->player));
    }
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {
	//A neutralplayer never issues an order.
    return this->territories;
}

vector<Territory*> NeutralPlayerStrategy::toAttack() {
	//A neutral player never issues an order.
    return this->territories;
}

/*
 * Cheater Player
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) {
	this->player = player;
}

void CheaterPlayerStrategy::issueOrder() {
	//The cheater will only steal territories from other players.
	this->toAttack();
}

//Cheater player doesn't defend
vector<Territory*> CheaterPlayerStrategy::toDefend() {
   //A cheater player cheats and bever defends its territories.
    return this->territories;
}

/*
 * Cheater automatically conquers all territories that are adjacent from conquered territories
 */
vector<Territory*> CheaterPlayerStrategy::toAttack() {
	vector<Territory*> cheatedTerritories;
	for (Territory* conquered : this->player->getTerritoryList()) {
		int row = conquered->getTerritoryID() - 1;
		for (int j = 0; j < this->getPlayer()->getMap()->getMatrix()[row].size(); j++) {
			if (this->getPlayer()->getMap()->getMatrix()[row][j].getGraphWeight() == 1) {
				string territoryName = this->getPlayer()->getMap()->getMatrix()[row][j].getTerritoryName();
				bool ownsTerritory = false;
				for (Territory* t : this->getPlayer()->getTerritoryList()) {
					if (territoryName == t->getTerritoryName()) {
						ownsTerritory = true;
						break;
					}
				}
				if (!ownsTerritory) {
					bool alreadyDisplayed = false;
					Territory* t = this->player->getTerritoryByName(this->player->THE_GAME_MAP->countries, territoryName);
					for (Territory* displayed : cheatedTerritories) {
						if (territoryName == displayed->getTerritoryName()) {
							alreadyDisplayed = true;
							break;
						}
					}
					if (!alreadyDisplayed) {
						cheatedTerritories.push_back(t);
						this->player->getTerritoryList().push_back(t);
						cout << "The cheater " << this->player->getName() << " stole: " << territoryName << endl;
					}
				}
			}
		}
	}
	this->player->issueOrderDone = true;
	return cheatedTerritories;
}











