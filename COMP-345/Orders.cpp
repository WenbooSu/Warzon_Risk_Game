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

//--Orders--
Order::Order() : owner(nullptr), if_executed(false)
{
    this->addObserver(this);
}

Order::Order(Player* theOwner, bool if_executed) : owner(theOwner), if_executed(false)
{
    this->addObserver(this);
}

Order::~Order()
{
    this->removeObserver(this);
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

std::string Order::stringToLog(const std::string& output) {
    return this->getOwner()->getName() + " has been has played their order with the following effect: " + this->effect;
}

//--OrdersList--
OrdersList::OrdersList()
{
    this->addObserver(this);
}

OrdersList::~OrdersList()
{
    this->removeObserver(this);
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
    this->notify(this->stringToLog(ord->getOwner()->getName()));
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

std::string OrdersList::stringToLog(const std::string& name) {
    return "An order been added to orderList of " + name;
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
        this->effect = "Deploying army on player territory " + territory->getTerritoryName() + "...";
        cout << this->effect << endl;
        territory->setArmies(army_deploy + territory->getArmies());
        getOwner()->addArmies((army_deploy * -1));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Army deployed!" << endl;
    }
    else
    {
        this->effect = "Invalid order: Cannot deploy on this territory";
        cout << this->effect << endl;
    }
    this->notify(this->stringToLog(this->effect));
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

    if (find(checkList.begin(), checkList.end(), source_territory) == checkList.end())
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
            //Check for the remaining number of armies commanded to deploy from source territory.
            if (source_territory->getArmies() >= this->army_deploy) {
                //If the source has enough, move them to the target
                adjacent_territory->setArmies(adjacent_territory->getArmies() + army_deploy);
                source_territory->setArmies(source_territory->getArmies() - army_deploy);
                this->effect = "Your army has advanced to friendly territory!";
                cout << this->effect << endl;
            }
            else if (source_territory->getArmies() <= 0) {
                //If the source has no armies, move nothing.
                this->effect = "No more remaining armies to be moved!";
                cout << this->effect << endl;
            }
            else {
                //If more armies are commanded than what the source contains, move remaining armies from source.
                adjacent_territory->setArmies(adjacent_territory->getArmies() + source_territory->getArmies());
                source_territory->setArmies(source_territory->getArmies() - source_territory->getArmies());
                this->effect = "Your army has advanced to friendly territory!";
                cout << this->effect << endl;
            }
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
                this->effect = "Congratulations, the territory " + source_territory->getTerritoryName() + " now belongs to you!";
                source_territory->setArmies(army_deploy);
                //Add the territory to the playr who advanced to it.
                this->getOwner()->getTerritoryList().push_back(source_territory);
                //Remove the territory from the previous player who owned it.
                Player* previous = source_territory->getPlayer();
                cout << this->effect << endl;
            }
            else {
                this->effect = "Your armies fought hard but the territory was not conquered.";
                cout << this->effect << endl;
            }
        }
    }
    else
    {
        this->effect = "Invalid order: Cannot advance on this enemy territory since it is neutral";
        cout << this->effect << endl;
    }
    this->notify(this->stringToLog(this->effect));
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
        this->effect = "Your opponent has lost half their army!";
        cout <<this->effect << endl;
    }
    else
    {
        this->effect = "Invalid bomb order";
        cout << this->effect << endl;
    }
    this->notify(this->stringToLog(this->effect));
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
        this->effect = "Blockade Complete on " + target_territory->getTerritoryName() + "!";
        cout <<this->effect << endl;
    }
    else
    {
       this->effect = "Invalid order: you cannot perform a blockade on this territory";
        cout <<this->effect << endl;
    }
    this->notify(this->stringToLog(this->effect));
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
    if (find(checkList.begin(), checkList.end(), source_territory) == checkList.end()) {
        cout << "The source territory " << source_territory->getTerritoryName() << " does not belong to you." << endl;
        return false;
    }

    if (!(find(checkList.begin(), checkList.end(), target_territory) != checkList.end())) {
        cout << "The target territory " << target_territory->getTerritoryName() << " does not belong to you." << endl;
        return false;
    }
    return true;
}

void Airlift::execute()
{
    if (validate())
    {
        int territoryArmies = source_territory->getArmies();
        cout << "Airlifting armies into target territory" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //Check that the armies deplaoyed is the number of remaining armies on the territory or less.
        if (this->army_deploy <= territoryArmies) {
            //If so, airlift the armies from the source to target territory.
            target_territory->setArmies(army_deploy + target_territory->getArmies());
            source_territory->setArmies(source_territory->getArmies() - army_deploy);
            this->effect = "Army airlifted onto the territory!";
            cout << this->effect << endl;
        }
        else if (territoryArmies <= 0) {
            //If the sourcce has no armies, move nothing.
            this->effect = source_territory->getTerritoryName() + " has no remaining armies!";
            cout << this->effect << endl;
        }
        else {
            //If more armies are commanded to airlift than what the source contains,
            //airlift all remaining armies from the source territory.
            target_territory->setArmies(territoryArmies + target_territory->getArmies());
            source_territory->setArmies(source_territory->getArmies() - territoryArmies);
            this->effect = "Army airlifted onto the territory!";
            cout << this->effect << endl;
        }
    }
    else
    {
        this->effect = "Invalid order, you cannot airlift into the territry you are own";
        cout << this->effect << endl;
    }
    this->notify(this->stringToLog(effect));
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
        this->effect = "Negotiations complete!";
        cout << this->effect << endl;
    }
    else
    {
        this->effect = "Invalid order, a player cannot negotiate with themselves";
        cout << this->effect << endl;
    }
}
