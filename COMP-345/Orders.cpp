#include "Orders.h"

#include <string>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

//--Orders--
Order::Order() : player("Default Player"), if_executed(false)
{
}

Order::Order(string thePlayer, bool if_executed) : player(thePlayer), if_executed(false)
{
}

Order::~Order()
{
}

Order::Order(const Order& o)
{
    this->player = o.player;
    this->if_executed = o.if_executed;
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
{
    if_executed = true;
}

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
    if(pos < list.size())
    {
        list.erase(list.begin() + pos);
    }
    else
    {
        cout << "Out of Range error" << endl;
    }    
}

void OrdersList::display()
{
    cout << "Orderlist has " << list.size() << " objects." << endl;
}

//--Deploy--
Deploy::Deploy() : Order(), territory("DefaultTerritory")
{}

Deploy::Deploy(string thePlayer, bool executed, string theTerritory) : Order(thePlayer, executed), territory(theTerritory)
{}

Deploy::~Deploy()
{   
}

Deploy::Deploy(const Deploy& deployObj) : Order(deployObj)
{
    this->territory = deployObj.territory;
}

bool Deploy::validate()
{
    return (territory != "DefaultTerritory");
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
{
}

Advance::Advance(const Advance& advanceObj) : Order(advanceObj)
{
    this->source_territory = advanceObj.source_territory;
    this->adjacent_territory = advanceObj.adjacent_territory;
}

Advance::Advance(string thePlayer, bool if_executed, string sourceTerritory, string adjacentTerritory) : Order(thePlayer, false), source_territory(sourceTerritory), adjacent_territory(adjacentTerritory)
{}

bool Advance::validate()
{
    return (source_territory != adjacent_territory);
}

void Advance::execute()
{
    if (validate())
    {
        cout << "Advancing army..." << endl;
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
{
}

Bomb::Bomb(string player, bool if_executed, string theTarget) : Order(player, false), target(theTarget)
{}

Bomb::Bomb(const Bomb& bombObj) : Order(bombObj)
{
    this->target = bombObj.target;
}

bool Bomb::validate()
{
    return (target != "DefaultTerritory");
}

void Bomb::execute()
{
    if (validate())
    {
        cout << "Bombing in progress" << endl;
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
{
}

Blockade::Blockade(string player, bool if_executed, string theTarget) : Order(player, false), target(theTarget)
{}

Blockade::Blockade(const Blockade& blockadeObj) : Order(blockadeObj)
{
    this->target = blockadeObj.target;
}

bool Blockade::validate()
{
    return (target != "DefaultTerritory");
}

void Blockade::execute()
{
    if (validate())
    {
        cout << "Blockade in progress" << endl;
    }
    else
    {
        cout << "Invalid order: you cannot perform a blockade on this territory" << endl;
    }
}

//--Airlift--
Airlift::Airlift() : Order(), source("Source Territory"), target("Target Territory")
{}

Airlift::~Airlift()
{
}

Airlift::Airlift(string player, bool if_executed, string theSource, string theTarget) : Order(player, false), source(theSource), target(theTarget)
{}

Airlift::Airlift(const Airlift& airliftObj) : Order(airliftObj)
{
    this->source = airliftObj.source;
    this->target = airliftObj.target;
}

bool Airlift::validate()
{
    return (source != target);
}

void Airlift::execute()
{
    if (validate())
    {
        cout << "Airlifting armies into target territory" << endl;
    }
    else
    {
        cout << "Invalid order, you cannot airlift into the territry you are own" << endl;
    }
}

//--Negotiate--
Negotiate::Negotiate() : Order(), enemy("Enemy Player")
{}

Negotiate::~Negotiate()
{}

Negotiate::Negotiate(string player, bool if_executed, string theEnemy) : Order(player, false), enemy(theEnemy)
{}

Negotiate::Negotiate(const Negotiate& negotiateObj) : Order(negotiateObj)
{
    this->enemy = negotiateObj.enemy;
}

bool Negotiate::validate()
{
   return (getPlayer() != enemy);
}

void Negotiate::execute()
{
    if (validate())
    {
        cout << "Negotiations in progress..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); //sleep for a second
        cout << "Negotiations complete!" << endl;
    }
    else
    {
        cout << "Invalid order, a player cannot negotiate with themselves" << endl;
    }
}
