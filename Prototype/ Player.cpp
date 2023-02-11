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
	this->territory = territoryList;
	this->handCard = hand;
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

Player::~Player()
{
	name.clear();
	territoryList.clear();  
	hand.clear();
	for (auto order : orderList)
	{
		delete order;
	}
	orderList.clear();

	
}

toDefend(vector<string*> territoryA){
	
	for (auto i = 0; i < terriortyA.size(); i++){
		 cout << terriortyA[i] << '/';
	}

}

toAttack(vector<string*> territoryD){
	
	for (auto i = 0; i < terriortyD.size(); i++){
		 cout << terriortyD[i] << '/';
	}
       

}

issueOrder(string orderParameter){
    Order *order = new Order(orderParameter);
	orderList.push_back(order);
	for (auto i = 0; i < orderList.size(); i++){
		 cout << orderList[i] << '/';
	}

}

getName(){

	return name;
}

vector<string*> getTerritoryList(){

	return terriortyList;
}
    
vector<Hand*> getHand(){

	return hand;
}
    
vector<Order*> getOrderList(){

	return orderList;
}


ostream& operator<<(ostream& os, Player player)
{
    os << player.getName << '/' << player.getTerritoryList << '/' << player.getOrderList;
    return os;
}
