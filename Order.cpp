#include "Order.h"

#include <string>
#include <queue>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

//--Orders--
Order::Order() : player("Default Player")
{
}

Order::Order(string thePlayer) : player(thePlayer)
{
}

Order::~Order()
{}

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
    vector<Order*> mylist;
    this->list = &mylist;
}

OrdersList::~OrdersList()
{
    for (Order* ord : *list)
    {
        delete ord;
    }
    list->clear();
}

OrdersList::OrdersList(const OrdersList& theOrdersList)
{
    for (auto order : *theOrdersList.list)
    {
        this->list->push_back(order);
    }
}

vector<Order*> OrdersList::getList()
{
    return *list;
}

void  OrdersList::add(Order *ord)
{
    list->push_back(ord);
}

void OrdersList::move(int oldPos, int newPos)
{
    list->insert(list->begin() + newPos, list->at(oldPos));
    list->erase(list->begin() + oldPos);
}

void OrdersList::remove(int pos)
{
    list->erase(list->begin() + pos);
}

void OrdersList::display()
{
    cout << "Orderlist has " << this->list->size() << " objects." << endl;
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
    return true; //change
}

void Deploy::execute()
{
    if (validate())
    {
        cout << "Deploying army" << endl;
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

ostream& operator << (std::ostream& out, const Deploy& d)
{
    return out << "Deloying army on " << d.territory << endl;
}

//--Advance--
Advance::Advance()
{}

Advance::~Advance()
{}

Advance::Advance(const Advance& advanceObj)
{}

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
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

//--Bomb--
Bomb::Bomb()
{}

Bomb::~Bomb()
{}

Bomb::Bomb(string player, string theTarget) : Order(player), target(theTarget)
{}

Bomb::Bomb(const Bomb& bombObj)
{}

bool Bomb::validate()
{
    return true; //change
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
Blockade::Blockade()
{}

Blockade::~Blockade()
{}

Blockade::Blockade(string player, string theTarget) : Order(), target(theTarget)
{}

Blockade::Blockade(const Blockade& blockadeObj)
{}

bool Blockade::validate()
{
    return true; //change
}

void Blockade::execute()
{
    if (validate())
    {
        cout << "Blockade in progress" << endl;
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

//--Airlift--
Airlift::Airlift()
{}

Airlift::~Airlift()
{}

Airlift::Airlift(string player, string theSource, string theTarget) : Order(), source(theSource), target(theTarget)
{}

Airlift::Airlift(const Airlift& airliftObj)
{}

bool Airlift::validate()
{
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
Negotiate::Negotiate()
{}

Negotiate::~Negotiate()
{}

Negotiate::Negotiate(string player, string theEnemy) : Order(), enemy(theEnemy)
{}

Negotiate::Negotiate(const Negotiate& negotiateObj)
{}

bool Negotiate::validate()
{
    return true; //change
}

void Negotiate::execute()
{
    if (validate())
    {
        cout << "Negotiations in progress" << endl;
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}
