#include "Player.h"
#include<iostream>
using namespace std;

Player::Player() 
{
	string name;
    vector<string*> territoryList;
    vector<Hand*> hand;
    vector<Order*> orderList;
}


Player::Player(string name, vector<string*> territoryList, vector<Card*> hand, vector<Order*> orderList) 
{
	this->name = name;
	this->terriorty = territoryList;
	this->handCard = hand;
	this->orderList = orderList;
}



//not deep copy
Player::Player(const Player& p) 
{
	this->name = p.name;
	this->terriortyList = p.terriortyList;
	this->hand = p.hand;
	this->orderList = p.orderList;

}

Player::~Player()
{
	name.clear();
	terriortyList.clear();  
	hand.clear();
	for (auto order : orderList)
	{
		delete order;
	}
	orderList.clear();

	
}

toDefend::output(){

}

toAttack::output(){

}

issueOrder(string territory){
    
}
