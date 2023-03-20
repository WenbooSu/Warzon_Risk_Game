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


Player* Order::getOwner()
{
    return owner;
}

//Stream insertion operator
ostream& operator<<(std::ostream& out, const Order& o)
{
    return out << "Performing an operation by " << o.owner->getName() << endl;
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
Deploy::Deploy() : Order(), army_deploy(0), territory(nullptr)
{}

Deploy::Deploy(Player* player1, bool if_executed, int army_to_deploy, Territory* territory) : Order(player1, if_executed), army_deploy(army_to_deploy), territory(territory)
{
}

Deploy::~Deploy()
{
}

Deploy::Deploy(const Deploy& deployObj) : Order(deployObj)
{
    this->territory = deployObj.territory;
    this->army_deploy = deployObj.army_deploy;
}

bool Deploy::validate()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();
    return (find(checkList.begin(), checkList.end(), territory) != checkList.end());
}

void Deploy::execute()
{
    if (validate())
    {
        cout << "Deploying army on player territory.." << endl;
        territory->setArmies(army_deploy + territory->getArmies());
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
    return out << "Deloying army on " << d.territory->getTerritoryName() << endl;
}

//--Advance--
Advance::Advance() : Order(), army_deploy(0), source_territory(nullptr), adjacent_territory(nullptr)
{}

Advance::~Advance()
{
}

Advance::Advance(const Advance& advanceObj) : Order(advanceObj)
{
    this->army_deploy = advanceObj.army_deploy;
    this->source_territory = advanceObj.source_territory;
    this->adjacent_territory = advanceObj.adjacent_territory;
}

Advance::Advance(Player *theOwner, bool if_executed, int army_to_deploy, Territory * sourceTerritory, Territory * adjacentTerritory) : Order(theOwner, false), army_deploy(army_to_deploy), source_territory(sourceTerritory), adjacent_territory(adjacentTerritory)
{
}

bool Advance::validate()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();
    //vector<Territory*> checkList = getOwner()->getTerritoryList();

    if (find(checkList.begin(), checkList.end(), source_territory) != checkList.end())
        return false;
    //Adjacency

    return true;
}

void Advance::execute()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();

    if (validate())
    {
        cout << "Advancing army..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (find(checkList.begin(), checkList.end(), adjacent_territory) != checkList.end())
        {            
            adjacent_territory->setArmies(adjacent_territory->getArmies() + army_deploy);
            source_territory->setArmies(source_territory->getArmies() - army_deploy);
            cout << "Your army has advanced to friendly territory!" << endl;
        }
        else
        {
            source_territory->setArmies(source_territory->getArmies() - army_deploy);

            while (army_deploy > 0 && source_territory->getArmies() > 0)
            {
                if ((rand() % 10) < 6)
                {
                    source_territory->setArmies(source_territory->getArmies() - 1);
                }
                if ((rand() % 10) < 7)
                {
                    army_deploy -= 1;
                }
            }

            if (source_territory->getArmies() == 0)
            {
                source_territory->setArmies(army_deploy);
                cout << "Congratulations, this territory now belongs to you!" << endl;
            }
        }
    }
    else
    {
        cout << "Invalid order: Cannot advance on this enemy territory since it is neutral" << endl;
    }
}

//--Bomb--
Bomb::Bomb() : Order(), target_territory(nullptr)
{}

Bomb::~Bomb()
{
}

Bomb::Bomb(Player * owner, bool if_executed, Territory *target_territory) : Order(owner, false), target_territory(target_territory)
{
}


Bomb::Bomb(const Bomb& bombObj) : Order(bombObj)
{
    this->target_territory = bombObj.target_territory;
}

bool Bomb::validate()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();

    if (find(checkList.begin(), checkList.end(), target_territory) != checkList.end())
        return false;

    //Adjacency thing

    return true;
}

void Bomb::execute()
{
    if (validate())
    {
        cout << "Bombing in progress" << endl;
        target_territory->setArmies(target_territory->getArmies() / 2);
        std::this_thread::sleep_for(std::chrono::seconds(2)); //sleep for 2s
        cout << "Your opponent has lost half their army!" << endl;
    }
    else
    {
        cout << "Invalid order" << endl;
    }
}

//--Blockade--
Blockade::Blockade() : Order(), target_territory(nullptr)
{}

Blockade::~Blockade()
{
}

Blockade::Blockade(Player * owner, bool if_executed, Territory *target_territory) : Order(owner, false), target_territory(target_territory)
{
}

Blockade::Blockade(const Blockade& blockadeObj) : Order(blockadeObj)
{
    this->target_territory = blockadeObj.target_territory;
}

bool Blockade::validate()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();
    return (find(checkList.begin(), checkList.end(), target_territory) != checkList.end());
}

void Blockade::execute()
{
    if (validate())
    {
        cout << "Blockade in progress..." << endl;
        target_territory->setArmies(target_territory->getArmies() * 2);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Blockade Complete!" << endl;
    }
    else
    {
        cout << "Invalid order: you cannot perform a blockade on this territory" << endl;
    }
}

//--Airlift--
Airlift::Airlift() : Order(), army_deploy(0), source_territory(nullptr), target_territory(nullptr)
{}

Airlift::~Airlift()
{
}

Airlift::Airlift(Player * owner, bool if_executed, int army_to_deploy, Territory * source_territory, Territory * target_territory) : Order(owner, false), army_deploy(army_to_deploy), source_territory(source_territory), target_territory(target_territory)
{
}

Airlift::Airlift(const Airlift& airliftObj) : Order(airliftObj)
{
    this->army_deploy = airliftObj.army_deploy;
    this->source_territory = airliftObj.source_territory;
    this->target_territory = airliftObj.target_territory;
}

bool Airlift::validate()
{
    vector<Territory*> checkList = getOwner()->getTerritoryList();

    if (!(find(checkList.begin(), checkList.end(), source_territory) != checkList.end()))
        return false;

    if (!(find(checkList.begin(), checkList.end(), target_territory) != checkList.end()))
        return false;

    return true;
}

void Airlift::execute()
{
    if (validate())
    {
        cout << "Airlifting armies into target territory" << endl;
        target_territory->setArmies(army_deploy + target_territory->getArmies());
        source_territory->setArmies(source_territory->getArmies() - army_deploy);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Army airlifted onto the territory!" << endl;
    }
    else
    {
        cout << "Invalid order, you cannot airlift into the territry you are own" << endl;
    }
}

//--Negotiate--
Negotiate::Negotiate() : Order(), enemyPlayer(nullptr)
{}

Negotiate::~Negotiate()
{}

Negotiate::Negotiate(Player *owner, bool if_executed, Player *enemyPlayer) : Order(owner, if_executed), enemyPlayer(enemyPlayer)
{
}

Negotiate::Negotiate(const Negotiate& negotiateObj) : Order(negotiateObj)
{
    this->enemyPlayer = negotiateObj.enemyPlayer;
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
        this->getOwner()->noAttack(enemyPlayer);
        enemyPlayer->noAttack(this->getOwner());
        std::this_thread::sleep_for(std::chrono::seconds(1)); //sleep for a second
        cout << "Negotiations complete!" << endl;
    }
    else
    {
        cout << "Invalid order, a player cannot negotiate with themselves" << endl;
    }
}
