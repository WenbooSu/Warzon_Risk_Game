#include <vector>
#include <string>
#include<iostream>
#include <algorithm>
#include "Player.h"

using namespace std;


Player::Player()
{
	string name;
	vector<string*> territoryList;
	vector<string*> hand;
	OrdersList orderList;
}


Player::Player(string name, vector<string*> territoryList, vector<string*> hand, OrdersList ordersList)
{
	this->name = name;
	this->territoryList = territoryList;
	this->hand = hand;
	this->orderList = orderList;
}

//not deep copy
Player::Player(const Player& p)
{
	this->name = p.name;
	this->territoryList = p.territoryList;
	this->hand = p.hand;
	this->orderList = p.orderList;
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

vector<string*> Player::getTerritoryList() {
	return this->territoryList;
}

vector<string*> Player::getHand() {
	return this->hand;
}

OrdersList Player::getOrderList() {
	return orderList;
}


ostream& operator<<(ostream& os, Player player)
{
	os << player.getName() << '/';
	vector<string*> t = player.getTerritoryList();
	for (int i = 0; i < t.size(); i++) {
		os << t[i];
	}
	OrdersList ot = player.getOrderList();
	ot.display();
	return os;
}

vector<string*> Player::compareTerritoryList(vector<string*> fullT1, vector<string*> t2) {
	vector<string*> terriortyD;
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
