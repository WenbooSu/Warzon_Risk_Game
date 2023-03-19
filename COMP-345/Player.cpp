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

//PlayerOrder::~PlayerOrder()
//{
//	for (auto territory : territoryList)
//	{
//		delete territory;
//	}
//	for (auto h : hand)
//	{
//		delete h;
//	}
//	for (auto order : orderList)
//	{
//		delete order;
//	}
//	orderList.clear();
//}

vector<Territory*> Player::toDefend() {
	string terrioryName = "";
	vector<Territory*> defend;
	cout << "List of your territories to defend: " << endl;
	for (Territory* territory : this->getTerritoryList()) {
		cout << territory->getTerritoryName() << endl;
	}
	while (terrioryName.compare("end") != 0) {
		cout << "Which territory to defend, or blank input to stop: ";
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

vector<Territory*> Player::toAttack() {

	/*cout << "List of territory to attack" << '/';
	cout << this->name;
	for (int i = 0; i < territoryD.size(); i++) {
		cout << territoryD[0] << '/';
	}*/
	vector<Territory*> attack;
	cout << "List of territories to defend: " << endl;
	for (Territory* territory : this->getTerritoryList()) {
		//cout << territory.get << endl;
	}

	return attack;
}

void Player::issueOrder() {//placeholder for now it is just the name of the order
	//Create a list of neighboring and your own territories to attack and defend.
	vector<Territory*> attack = this->toAttack();
	vector<Territory*> defend = this->toDefend();
	//Now issue deploy orders to the territories to defend for the remaining number of armies.
	int numDeploy;
	while (*this->armies > 0) {
		for (Territory* territory : defend) {
			cout << "Remaining armies: " + *this->armies << endl;
			cout << "How many armies would you like to deploy to " + territory->getTerritoryName() + ": ";
			cin >> numDeploy;
			cout << endl;
			//If more are ordered than available, set it to all available armies remaining.
			if (numDeploy > *this->armies) {
				numDeploy = *this->armies;
			}
			*this->armies -= numDeploy;
			//When adding armies to defend your territory, a deploy order must be issued.
			this->orderList.add(new Deploy());
			cout << numDeploy + " armies are ordreed to be deployed to " + territory->getTerritoryName() << endl;
			if (*this->armies <= 0) {
				*this->armies = 0;
				break;
			}
		}
	}
	//Commence issuing advance orders: moving armies between your own teritories, or issuing an attack
	cout << "Advance Orders: " << endl;
	string command = "";
	string baseTerritory;
	string targetTerritory;
	int armiesMoving = 0;
	while (command != "end") {
		cout << "Choose your territory: ";
		cin >> baseTerritory;
		cout << endl;
		cout << "Choose a territory to move your armies to attack or defend: ";
		cin >> targetTerritory;
		cout << endl;
		cout << "How many armies would you like to move: ";
		cin >> armiesMoving;
		cout << endl;
		this->orderList.add(new Advance());
		cout << "Moving " + armiesMoving << " armies from " + baseTerritory << " to " + targetTerritory << endl;
	}
	//From a list of the player's cards, execute one of the orders.
	cout << this->name + "'s current cards:" << endl;
	this->getHand();

	//Order* order = new Order(orderParameter, false);//using placeholder class to avoid complication
	//this->orderList.add(order);
	//this->orderList.display();
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
