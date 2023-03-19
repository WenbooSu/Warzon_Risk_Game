#include "Orders.h"
#include "Player.h"
#include "Card.h"
#include "MapLoader.h"

#include <string>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

//--Orders--
Order::Order() : owner(nullptr), if_executed(false)
{
}

Order::Order(Player* theOwner, bool if_executed) : owner(theOwner), if_executed(false)
{
}

Order::~Order()
{
}

Order::Order(const Order& o)
{
    this->owner = o.owner;
    this->if_executed = o.if_executed;
}

string Order::getPlayer()
{
    return player;
}

Player* Order::getOwner()
{
    return owner;
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

void  OrdersList::add(Order* ord)
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
    if (pos < list.size())
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
Deploy::Deploy() : Order(), army_deploy(0), territory1(nullptr)
{}

/*Deploy::Deploy(Player* player, bool if_executed, string territory) : Order(player, if_executed), territory(territory)
{
}*/

Deploy::Deploy(Player* player1, bool if_executed, int army_to_deploy, Territory* territory) : Order(player1, if_executed), army_deploy(army_to_deploy), territory1(territory)
{
}

Deploy::~Deploy()
{
}

Deploy::Deploy(const Deploy& deployObj) : Order(deployObj)
{
    this->territory1 = deployObj.territory1;
    this->army_deploy = deployObj.army_deploy;
}

bool Deploy::validate()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();
    return (find(checkList.begin(), checkList.end(), territory1) != checkList.end());
}

void Deploy::execute()
{
    if (validate())
    {
        cout << "Deploying army on player territory.." << endl;
        territory1->setArmies(army_deploy + territory1->getArmies());
        getOwner()->addArmies((army_deploy * -1));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Army deployed!" << endl;
    }
    else
    {
        cout << "Invalid order: Cannot deploy on this territory" << endl;
    }
}

//Stream insertion operator
ostream& operator << (std::ostream& out, const Deploy& d)
{
    return out << "Deloying army on " << d.territory1->getTerritoryName() << endl;
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

Advance::Advance(Player *theOwner, bool if_executed, string sourceTerritory, string adjacentTerritory) : Order(theOwner, false), source_territory(sourceTerritory), adjacent_territory(adjacentTerritory)
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

Bomb::Bomb(Player *owner, bool if_executed, string theTarget) : Order(owner, false), target(theTarget)
{}


Bomb::Bomb(const Bomb& bombObj) : Order(bombObj)
{
    this->target = bombObj.target;
}

//string Bomb::get

bool Bomb::validate()
{
    return (target != "Target Territory");
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

Blockade::Blockade(Player *owner, bool if_executed, string theTarget) : Order(owner, false), target(theTarget)
{}

Blockade::Blockade(const Blockade& blockadeObj) : Order(blockadeObj)
{
    this->target = blockadeObj.target;
}

bool Blockade::validate()
{
    return (target != "Target Territory");
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

Airlift::Airlift(Player *owner, bool if_executed, string theSource, string theTarget) : Order(owner, false), source(theSource), target(theTarget)
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
Negotiate::Negotiate() : Order(), enemy("Enemy Player"), enemyPlayer(nullptr)
{}

Negotiate::~Negotiate()
{}

Negotiate::Negotiate(Player *owner, bool if_executed, Player *enemyPlayer) : Order(owner, if_executed), enemyPlayer(enemyPlayer)
{
}

Negotiate::Negotiate(const Negotiate& negotiateObj) : Order(negotiateObj)
{
    this->enemy = negotiateObj.enemy;
}

bool Negotiate::validate()
{
    return (this->getOwner() != enemyPlayer);
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
