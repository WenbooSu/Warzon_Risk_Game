#include <vector>
#include <string>
#include "OrderTemp.h"
#include "MapLoader.h"
#include<iostream>
#include <algorithm>
using namespace std;

Player::Player() 
{
	string name;
    vector<Territory*> territoryList;
    vector<Hand*> hand;
    vector<Order*> orderList;
}


Player::Player(string name, vector<Territory*> territoryList, vector<string*> hand, vector<string*> orderList) 
{
	this->name = name;
	this->territoryList = territoryList;
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

toDefend(vector<Territory*> territoryA){
	
	cout<<"List of territory to defend";
	for (int i = 0; i < terriortyA.size(); i++){
		 cout << terriortyA[i] << '/';
	}

}

toAttack(vector<Territory*> territoryD){
	
	cout<<"List of territory to attack";
	for (int i = 0; i < terriortyD.size(); i++){
		 cout << terriortyD[i] << '/';
	}
       

}

issueOrder(string orderParameter){//placeholder for now it is just the name of the order
    OrderTemp *order = new OrderTemp(orderParameter);//using placeholder class to avoid complication
	orderList.push_back(order);
	for (int i = 0; i < orderList.size(); i++){//show the list of order
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

vector<Territory*> compareTerritoryList(vector<Territory*> fullT1,vector<Territory*> t2) {

	vector<Territory*> terriortyD;

    
 for (int i = 0; i < t2.size(); i++){
	
    if (find(v.begin(), v.end(), t2[i]) != v.end()) {
        cout << "Element found";
    }
    else {
        cout << "Element not found";
		terriortyD.push_back(t2[i]);
    }
 }
    return terriortyD;
}

OrderTemp::OrderTemp() 
{
	string title = "No order";
}


OrderTemp::OrderTemp(string titlle) 
{
	this->title = title;
}



//not deep copy
OrderTemp::OrderTemp(const OrderTemp& ot) 
{
	this->title = ot.title;

}

