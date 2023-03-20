#include <vector>
#include <string>
#include<iostream>
#include <algorithm>
#include "Player.h"
#include "MapLoader.h"

using namespace std;


Player::Player(){
	string name;
	vector<string*> territoryList;
	vector<string*> hand;
	OrdersList orderList;
	this->armies = new int(0);
}


Player::Player(string name, vector<Territory*> territoryList, playerHand hand, OrdersList ordersList){
	this->name = name;
	this->territoryList = territoryList;
	this->hand = hand;
	this->orderList = orderList;
	this->armies = new int(0);
}

//not deep copy
Player::Player(const Player& p){
	this->name = p.name;
	this->territoryList = p.territoryList;
	this->hand = p.hand;
	this->orderList = p.orderList;
	*this->armies = *p.armies;
}

Player::~Player() {
	delete this->armies;
	for (Territory* t : this->territoryList) {
		delete t;
	}
}

vector<Territory*> Player::toDefend() {
	string terrioryName = "";
	vector<Territory*> defend;
	cout << "List of your territories to defend: " << endl;
	for (Territory* territory : this->getTerritoryList()) {
		cout << territory->getTerritoryName() << endl;
	}
	while (terrioryName.compare("end") != 0) {
		cout << "Which territory to defend, or input end to stop: ";
		cin >> terrioryName;
		for (Territory* territory : this->getTerritoryList()) {
			if (territory->getTerritoryName() == terrioryName) {
				defend.push_back(territory);
				cout << terrioryName + " has been added to list of territories to defend." << endl;
				break;
			}
		}
	}
	return defend;
}

vector<Territory*> Player::toAttack(vector<Territory> allTerritories) {
	vector<Territory*> attack;
	cout << "List of territories to attack: " << endl;
	bool found = false;
	Territory* enemy;
	for (Territory t : allTerritories) {
		for (Territory* territory : this->getTerritoryList()) {
			enemy = territory;
			if (territory->getTerritoryName() == t.getTerritoryName()) {
				found = true;
				break;
			}
		}
		if (!found) {
			attack.push_back(enemy);
			cout << enemy->getTerritoryName() << endl;
		}
		found = false;
	}
	return attack;
}

void Player::issueOrder(Deck* deck, vector<Player*> players, vector<Territory> mapTerritories) {
	//Create a list of neighboring and your own territories to attack and defend.
	vector<Territory*> attack = this->toAttack(mapTerritories);
	vector<Territory*> defend = this->toDefend();
	//Now issue deploy orders to the territories to defend for the remaining number of armies.
	int numDeploy;
	int availableArimes = *this->armies;
	cout << "\nCurrent Player:\t" << this->name;
	while (availableArimes > 0) {
		for (Territory* territory : defend) {
			cout << "Remaining armies: ";
			cout << availableArimes << endl;
			cout << "How many armies would you like to deploy to " << territory->getTerritoryName() << ": " << endl;
			cin >> numDeploy;
			//If more are ordered than available, set it to all available armies remaining.
			if (numDeploy > availableArimes) {
				numDeploy = availableArimes;
			}
			//When adding armies to defend your territory, a deploy order must be issued.
			this->orderList.add(new Deploy(this, false, numDeploy, territory));
			availableArimes -= numDeploy;
			cout << endl;
			cout << numDeploy << " armies are ordered to be deployed to " << territory->getTerritoryName() << endl;
			if (availableArimes <= 0) {
				break;
			}
		}
	}
	//Commence issuing advance orders: moving armies between your own teritories, or issuing an attack
	cout << "Advance Orders: " << endl;
	string continueAdvance = "";
	string baseTerritory;
	string targetTerritory;
	int armiesMoving = 0;
	while (continueAdvance != "end") {
		cout << "Choose your territory: ";
		cin >> baseTerritory;
		cout << "Choose a territory to move your armies to attack or defend: ";
		cin >> targetTerritory;
		cout << "How many armies would you like to move: ";
		cin >> armiesMoving;
		this->orderList.add(new Advance());
		cout << "Continue issuing advance orders? Input end to stop." << endl;
		cin >> continueAdvance;
	}
	//From a list of the player's cards, execute one of the orders.
	cout << this->name + "'s current cards:" << endl;
	this->getHand().showHand();
	cout << "Select one of the cards by number to issue the corresponding order." << endl;
	int cardNum = 0;
	cin >> cardNum;
	while (cardNum < 1 || cardNum > this->getHand().hand.size()) {
		cout << "Please try again.";
		cin >> cardNum;
	}
	Card card = this->getHand().play(cardNum - 1, *deck);
	//Based card name, issue the respective order, and give the correct respective input to issue the order.
	if (card.CardType == "airlift") {
		string sourceTerritory;
		string enemyTarget;
		int numArmies;
		cout << "What is the source territory to airlift from: ";
		cin >> sourceTerritory;
		cout << "What is the airlift destination: ";
		cin >> enemyTarget;
		cout << "How many armies would you like to arilift: ";
		cin >> numArmies;
		this->orderList.add(new Airlift(this, false, numArmies,
			getTerritoryByName(defend, sourceTerritory), getTerritoryByName(defend, targetTerritory)));
	}
	else if (card.CardType == "bomb") {
		string enemyTerritory;
		cout << "What enemy teritory would you like to target: ";
		cin >> enemyTerritory;
		this->orderList.add(new Bomb(this, false, getTerritoryByName(attack, enemyTerritory)));
	}
	else if (card.CardType == "blockade") {
		string playerTerritory;
		cout << "Which territory would you like to blockade: ";
		cin >> playerTerritory;
		this->orderList.add(new Blockade(this, false, getTerritoryByName(defend, playerTerritory)));
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
		this->orderList.add(new Negotiate(this, false, enemyPlayer));
	}
	cout << "\n" << endl;
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

playerHand Player::getHand() {
	return this->hand;
}

void Player::addToHand(Card card) {
	this->hand.add(card);
}

OrdersList Player::getOrderList() {
	return orderList;
}

void Player::noAttack(Player* ally)
{
	this->noAttackList.push_back(ally);
}

int* Player::getArmies() {
	return this->armies;
}

void Player::addArmies(int added) {
	*this->armies += added;
}

ostream& operator<<(ostream& os, Player player){
	os << player.getName() << '/';
	vector<Territory*> t = player.getTerritoryList();
	for (int i = 0; i < t.size(); i++) {
		os << t[i];
	}
	OrdersList ot = player.getOrderList();
	ot.display();
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
