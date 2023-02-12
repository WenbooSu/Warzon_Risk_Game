#include "Orders.h"
#include "Player.h"
#include "Card.h"

#include <string>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

//--Orders--
Order::Order() : player("Default Player")
{
}

Order::Order(string thePlayer) : player(thePlayer)
{
}

Order::~Order()
{
    
}

Order::Order(const Order& o)
{
    this->player = o.player;
}

string Order::getPlayer()
{
    return player;
}

bool Order::validate()
{
    return false;
}

void Order::execute()
{}

//Stream insertion operator
ostream& operator<<(std::ostream& out, const Order& o)
{
    return out << "Performing an operation by " << o.player << endl;
}

//--OrdersList--
OrdersList::OrdersList()
{
}

OrdersList::~OrdersList()
{
    for (Order* ord : list)
    {
        delete ord;
    }
    list.clear();
}

OrdersList::OrdersList(const OrdersList& theOrdersList)
{
    for (auto order : theOrdersList.list)
    {
        list.push_back(order);
    }
}

vector<Order*> OrdersList::getList()
{
    return list;
}

void  OrdersList::add(Order *ord)
{
    list.push_back(ord);
}

void OrdersList::move(int oldPos, int newPos)
{
    list.insert(list.begin() + newPos, list.at(oldPos));
    list.erase(list.begin() + oldPos);
}

void OrdersList::remove(int pos)
{
    list.erase(list.begin() + pos);
}

void OrdersList::display()
{
    cout << "Orderlist has " << list.size() << " objects." << endl;
}

//--Deploy--
Deploy::Deploy() : Order(), territory("DefaultTerritory")
{}

Deploy::Deploy(string thePlayer, string theTerritory) : Order(thePlayer), territory(theTerritory)
{}

Deploy::~Deploy()
{}

Deploy::Deploy(const Deploy& deployObj) : Order(deployObj)
{
    this->territory = deployObj.territory;
}

bool Deploy::validate()
{
    //return Player object's territory list then check if intended territory is in there
    //vector<string*>  terrList = player.getTerritoryList(); 
    //return (std::find(terrList.begin(), terrList.end(), territory) != terrList.end())
    return true; //change
}

void Deploy::execute()
{
    if (validate())
    {
        cout << "Deploying army on player territory" << endl;
    }
    else
    {
        cout << "Invalid order: Cannot deploy on this territory" << endl;
    }
}

//Stream insertion operator
ostream& operator << (std::ostream& out, const Deploy& d)
{
    return out << "Deloying army on " << d.territory << endl;
}

//--Advance--
Advance::Advance() : Order(), source_territory("Source Territory"), adjacent_territory("Adjacent Territory")
{}

Advance::~Advance()
{}

Advance::Advance(const Advance& advanceObj) : Order(advanceObj)
{
    this->source_territory = advanceObj.source_territory;
    this->adjacent_territory = advanceObj.adjacent_territory;
}

Advance::Advance(string thePlayer, string sourceTerritory, string adjacentTerritory) : Order(thePlayer), source_territory(sourceTerritory), adjacent_territory(adjacentTerritory)
{}

bool Advance::validate()
{

    return true; //change
}

void Advance::execute()
{
    if (validate())
    {
        cout << "Advancing army" << endl;
        //return Player object's territory list then check if intended territory is in there
        //vector<string*>  terrList = player.getTerritoryList(); 
        //if (std::find(terrList.begin(), terrList.end(), territory) != terrList.end()) {cout << "Army has arrived << endl;}
        //else {cout << "Attack underway" << endl; std::this_thread::sleep_for(std::chrono::seconds(2)); cout << "Attack complete" << endl;}
    }
    else
    {
        cout << "Invalid order: Cannot advance on this enemy territory since it is neutral" << endl;
    }
}

//--Bomb--
Bomb::Bomb() : Order(), target("Target Territory")
{}

Bomb::~Bomb()
{}

Bomb::Bomb(string player, string theTarget) : Order(player), target(theTarget)
{}

Bomb::Bomb(const Bomb& bombObj) : Order(bombObj)
{
    this->target = bombObj.target;
}

bool Bomb::validate()
{
    //return Player object's territory list then check if intended territory is in there
    //vector<string*>  terrList = player.getTerritoryList(); 
    //return (std::find(terrList.begin(), terrList.end(), territory) != terrList.end())
    return true; //change
}

void Bomb::execute()
{
    if (validate())
    {
        cout << "Bombing in progress" << endl;
        //player.army = player.army/2;
        std::this_thread::sleep_for(std::chrono::seconds(2)); //sleep for 2s
        cout << "Your opponent has lost half their army!" << endl;
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

//--Blockade--
Blockade::Blockade() : Order(), target("Target Territory")
{}

Blockade::~Blockade()
{}

Blockade::Blockade(string player, string theTarget) : Order(), target(theTarget)
{}

Blockade::Blockade(const Blockade& blockadeObj) : Order(blockadeObj)
{
    this->target = blockadeObj.target;
}

bool Blockade::validate()
{
    //return Player object's territory list then check if intended territory is in there
    //vector<string*>  terrList = player.getTerritoryList(); 
    //return (std::find(terrList.begin(), terrList.end(), territory) != terrList.end())
    return true; //change
}

void Blockade::execute()
{
    if (validate())
    {
        cout << "Blockade in progress" << endl;
        //player.army = player.army * 3;
        //territory.status = 'N'
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

//--Airlift--
Airlift::Airlift() : Order(), source("Source Territory"), target("Target Territory")
{}

Airlift::~Airlift()
{}

Airlift::Airlift(string player, string theSource, string theTarget) : Order(), source(theSource), target(theTarget)
{}

Airlift::Airlift(const Airlift& airliftObj) : Order(airliftObj)
{
    this->source = airliftObj.source;
    this->target = airliftObj.target;
}

bool Airlift::validate()
{
    //return Player object's territory list then check if intended territory is in there
    //vector<string*>  terrList = player.getTerritoryList(); 
    //return (std::find(terrList.begin(), terrList.end(), territory) != terrList.end())
    return true; //change
}

void Airlift::execute()
{
    if (validate())
    {
        cout << "Airlifting armies into target territory" << endl;
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

//--Negotiate--
Negotiate::Negotiate() : Order(), enemy("Enemy Player")
{}

Negotiate::~Negotiate()
{}

Negotiate::Negotiate(string player, string theEnemy) : Order(), enemy(theEnemy)
{}

Negotiate::Negotiate(const Negotiate& negotiateObj) : Order(negotiateObj)
{
    this->enemy = negotiateObj.enemy;
}

bool Negotiate::validate()
{
    //return player == enemy;
    return true; //change
}

void Negotiate::execute()
{
    if (validate())
    {
        cout << "Negotiations in progress" << endl;
        //Territory/string* enemyTerrList = enemy.getTerritoryList(); 
        //for (auto territory : enemyTerrList) {territory.status = 'N';}
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}
