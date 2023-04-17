#include <vector>
#include <string>
#include<iostream>
#include <algorithm>
#include "Player.h"
#include "PlayerStrategy.h"

using namespace std;


Player::Player(){
	string name;
	vector<string*> territoryList;
	OrdersList o;
	this->orderList = new OrdersList();
	this->hand = new playerHand();
	this->armies = 0;
	this->deck = nullptr;
}


Player::Player(string name, vector<Territory*> territoryList, playerHand* hand, OrdersList* ordersList){
	this->name = name;
	this->territoryList = territoryList;
	this->hand = hand;
	this->orderList = orderList;
	this->armies = 0;
	this->deck = nullptr;
}

Player::Player(std::string name, Map* map, playerHand* hand, OrdersList* ordersList) {
	this->name = name;
	this->THE_GAME_MAP = map;
	this->hand = hand;
	this->orderList = orderList;
	this->armies = 0;
	this->deck = nullptr;
}

//not deep copy
Player::Player(const Player& p){
	this->name = p.name;
	this->territoryList = p.territoryList;
	this->hand = p.hand;
	this->orderList = p.orderList;
	this->armies = p.armies;
	this->deck = nullptr;
}

Player::~Player() {
	for (Territory* t : this->territoryList) {
		delete t;
	}
}

vector<Territory*> Player::toDefend() {
	return this->ps->toDefend();
}

vector<Territory*> Player::toAttack() {
	return this->ps->toAttack();
}

void Player::issueOrder(Deck* deck, vector<Player*> players, Map* map) {
	this->ps->issueOrder();
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
