#include <vector>
#include <string>
#include<iostream>
#include <algorithm>
#include "Player.h"

using namespace std;


Player::Player(){
	string name;
	vector<string*> territoryList;
	OrdersList o;
	this->orderList = new OrdersList();
	this->hand = new playerHand();
	this->armies = 0;
}


Player::Player(string name, vector<Territory*> territoryList, playerHand* hand, OrdersList* ordersList){
	this->name = name;
	this->territoryList = territoryList;
	this->hand = hand;
	this->orderList = orderList;
	this->armies = 0;
}

Player::Player(std::string name, Map* map, playerHand* hand, OrdersList* ordersList) {
	this->name = name;
	this->THE_GAME_MAP = map;
	this->hand = hand;
	this->orderList = orderList;
	this->armies = 0;
}

//not deep copy
Player::Player(const Player& p){
	this->name = p.name;
	this->territoryList = p.territoryList;
	this->hand = p.hand;
	this->orderList = p.orderList;
	this->armies = p.armies;
}

Player::~Player() {
	for (Territory* t : this->territoryList) {
		delete t;
	}
}

vector<Territory*> Player::toDefend() {
	string terrioryName = "";
	vector<Territory*> defend;
	cout << "\nList of your territories to defend: " << endl;
	for (Territory* territory : this->getTerritoryList()) {
		cout << territory->getTerritoryName() << endl;
		defend.push_back(territory);
	}
	return defend;
}

vector<Territory*> Player::toAttack(vector<Territory*> allTerritories) {
	vector<Territory*> attack;
	cout << "\nList of territories to attack: " << endl;
	bool found = false;
	Territory* enemyTerritory;
	/*
	
	
	FIND ADJACENT ENEMY TERRITORIES
	
	
	*/
	for (Territory* territory : allTerritories) {
		for (Territory* playerTerritory : this->getTerritoryList()) {
			enemyTerritory = territory;
			if (playerTerritory->getTerritoryName() == territory->getTerritoryName()) {
				found = true;
				break;
			}
		}
		if (!found) {
			attack.push_back(enemyTerritory);
			cout << enemyTerritory->getTerritoryName() << endl;
		}
		found = false;
	}
	return attack;
}

void Player::issueOrder(Deck* deck, vector<Player*> players, MapLoader* map) {
	//Create a list of neighboring and your own territories to attack and defend.
	cout << "\n\nIt is now " << this->name << "'s turn." << endl;
	//Now issue deploy orders to the territories to defend for the remaining number of armies.
	int numDeploy;
	int availableArimes = this->getArmies() - this->armiesUsed;
	cout << "\nCurrent Player:\t" << this->name << endl;
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
		this->orderList->add(new Deploy(this, false, numDeploy, territory));
		this->armiesUsed += numDeploy;
		cout << endl;
		cout << numDeploy << " armies are ordered to be deployed to " << territory->getTerritoryName() << endl;
	}
	else {
		//Commence issuing advance orders: moving armies between your own teritories, or issuing an attack
		//Or using cards in player's hand.
		vector<Territory*> attackTerritories = this->toAttack(map->countries);
		vector<Territory*> defendTerritories = this->toDefend();
		cout << "Available Orders: " << endl;
		cout << "0 Advance Order" << endl;
		//From a list of the player's cards, execute one of the orders.
		cout << "Current cards : " << endl;
		this->getHand()->showHand();
		//Continue until a valid choice has been entered.
		int choice = -1;
		int numCards = this->getHand()->hand.size();
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
				Territory* baseTerritory = getTerritoryByName(this->getTerritoryList(), baseTerritoryName);
				cout << "Choose a territory that belongs to enemy to attack or your own to defend: ";
				cin >> targetTerritoryName;
				//Check both the defend and the attack territories pointer list for the advanced order.
				Territory* adjacentTerritory = getTerritoryByName(attackTerritories, targetTerritoryName);
				if (adjacentTerritory == nullptr) {
					adjacentTerritory = getTerritoryByName(defendTerritories, targetTerritoryName);
				}
				cout << "How many armies would you like to move: ";
				cin >> armiesMoving;
				this->orderList->add(new Advance(this, false, armiesMoving, baseTerritory, adjacentTerritory));
				cout << "Continue issuing advance orders? Input end to stop." << endl;
			}
			else if (choice <= this->getHand()->hand.size() && this->getHand()->hand.size() > 0 && choice > 0) {
				Card card = this->getHand()->play(choice - 1, *deck);
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
					this->orderList->add(new Airlift(this, false, numArmies,
						getTerritoryByName(this->getTerritoryList(), sourceTerritory), getTerritoryByName(this->getTerritoryList(), destinationTarget)));
				}
				else if (card.CardType == "bomb") {
					string enemyTerritory;
					cout << "What enemy teritory would you like to target: ";
					cin >> enemyTerritory;
					this->orderList->add(new Bomb(this, false, getTerritoryByName(attackTerritories, enemyTerritory)));
				}
				else if (card.CardType == "blockade") {
					string playerTerritory;
					cout << "Which territory would you like to blockade: ";
					cin >> playerTerritory;
					this->orderList->add(new Blockade(this, false, getTerritoryByName(this->getTerritoryList(), playerTerritory)));
				}
				else if (card.CardType == "negotiate") {
					string enemyPlayerName;
					cout << "Which player would you like to negtoiate with: ";
					cin >> enemyPlayerName;
					Player* enemyPlayer = nullptr;
					for (Player* p : players) {
						if (p->name == enemyPlayerName) {
							enemyPlayer = p;
							break;
						}
					}
					this->orderList->add(new Negotiate(this, false, enemyPlayer));
				}
				cout << "\n" << endl;
			}
		}
	}
}

Territory* Player::getTerritoryByName(vector<Territory*> territories, string name) {
	for (Territory* t : territories) {
		if (t->getTerritoryName() == name) {
			return t;
		}
	}
	return nullptr;
}

string Player::getName() {
	return this->name;
}

void Player::setName(string name) {
	this->name = name;
}

vector<Territory*> Player::getTerritoryList() {
	return this->territoryList;
}

void Player::setTerritoryList(vector<Territory*> territoryList) {
	this->territoryList = territoryList;
}

void Player::addTerritory(Territory* territory) {
	this->territoryList.push_back(territory);
}

playerHand* Player::getHand() {
	return this->hand;
}

void Player::addToHand(Card card) {
	this->hand->add(card);
}

OrdersList* Player::getOrderList() {
	return orderList;
}

void Player::noAttack(Player* ally)
{
	this->noAttackList.push_back(ally);
}

int Player::getArmies() {
	return this->armies;
}

void Player::addArmies(int added) {
	this->armies += added;
}

ostream& operator<<(ostream& os, Player player){
	os << player.getName() << '/';
	vector<Territory*> t = player.getTerritoryList();
	for (int i = 0; i < t.size(); i++) {
		os << t[i];
	}
	OrdersList* ot = player.getOrderList();
	ot->display();
	return os;
}

vector<Territory*> Player::compareTerritoryList(vector<Territory*> fullT1, vector<Territory*> t2) {
	vector<Territory*> terriortyD;
	for (int i = 0; i < t2.size(); i++) {

		if (find(fullT1.begin(), fullT1.end(), fullT1[i]) != fullT1.end()) {
			cout << "Element found";
		}
		else {
			cout << "Element not found";
			terriortyD.push_back(t2[i]);
		}
	}
	return terriortyD;
}

void Player::setPlayerStrategy(PlayerStrategy* psp) {
	this->ps = psp;
}

Map* ::Player::getMap() {
	return this->THE_GAME_MAP;
}

bool Player::beingAttacked() {
	int current = this->armies_record[this->armies_record.size() - 1];
	int last = this->armies_record[this->armies_record.size() - 2];
	if (current < last)
	{
		return true;
	}
	else
	{
		return false;
	}
}
