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

void Player::toDefend(vector<string*> territoryA) {

	cout << "List of territory to defend" << '/';
	cout << this->name;
	for (int i = 0; i < territoryA.size(); i++) {
		cout << territoryA[0] << '/';
	}

}

void Player::toAttack(vector<string*> territoryD) {

	cout << "List of territory to attack" << '/';
	cout << this->name;
	for (int i = 0; i < territoryD.size(); i++) {
		cout << territoryD[0] << '/';
	}
}

void Player::issueOrder(string orderParameter) {//placeholder for now it is just the name of the order
	Order* order = new Order(orderParameter, false);//using placeholder class to avoid complication
	this->orderList.add(order);
	this->orderList.display();
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

void Player::setTerritoryList(vector<Territory*>) {

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
