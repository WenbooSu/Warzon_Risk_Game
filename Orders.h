#pragma once

#include <string>
#include <queue>

using namespace std;

class Player; //Forward declaration of the Player class
class Territory; //Forward declaration of the Territory class

class Order
{
public:
    //Constructors
    Order();
    Order(Player* owner, bool if_executed);
    ~Order();
    Order(const Order& theOrder);

    //Accessors
    Player* getOwner();
    
    //Methods
    virtual bool validate() = 0;
    virtual void execute() = 0;

    friend ostream& operator << (ostream& out, const Order& o);

private:
    Player *owner;
    bool if_executed;
};

class OrdersList //A list object that holds Order objects
{
public:
    //Constructors
    OrdersList();
    ~OrdersList();
    OrdersList(const OrdersList& theOrdersList);

    //Accessors 
    vector<Order*> getList();

    void add(Order* ord);
    void move(int oldPos, int newPos);
    void remove(int pos);
    void display();//Might have to take out

private:
    vector<Order*> list{};
};

class Deploy : public Order
{
public:
    //Constructors
    Deploy();
    Deploy(Player* owner, bool if_executed, int army_deploy, Territory* territory);
    ~Deploy();
    Deploy(const Deploy& deployObj);

    bool validate() override;
    void execute() override;

    friend ostream& operator << (ostream& out, const Deploy& d);

private:
    int army_deploy;
    Territory *territory;
};

class Advance : public Order
{
public:
    //Constructors
    Advance();
    ~Advance();
    Advance(Player* owner, bool if_executed, string source_territory, string adjacent_territory);
    Advance(Player *owner, bool if_executed, Territory* source_territory1, Territory* adjacent_territory1);
    Advance(const Advance& advanceObj);

    bool validate() override;
    void execute() override;

private:
    string source_territory; 
    Territory *source_territory1;
    string adjacent_territory; 
    Territory *adjacent_territory1;
};

class Bomb : public Order
{
public:
    //Constructors
    Bomb();
    ~Bomb();
    Bomb(Player *owner, bool if_executed, string target);
    Bomb(const Bomb& bombObj);

    bool validate() override;
    void execute() override;

private:
    string target; //Territory target;
};

class Blockade : public Order
{
public:
    //Constructors
    Blockade();
    ~Blockade();
    Blockade(Player *owner, bool if_executed, string target);
    Blockade(const Blockade& blockadeObj);

    bool validate() override;
    void execute() override;

private:
    string target; //Territory target;
};

class Airlift : public Order
{
public:
    //Constructors
    Airlift();
    ~Airlift();
    Airlift(Player *owner, bool if_executed, string source, string target);
    Airlift(const Airlift& airliftObj);

    bool validate() override;
    void execute() override;

private:
    string source; //Territory source_territory;
    string target; //Territory adjacent_territory;
};

class Negotiate : public Order
{
public:
    //Constructors
    Negotiate();
    ~Negotiate();
    Negotiate(Player *owner, bool if_executed, Player *enemyPlayer);
    Negotiate(const Negotiate& negotiateObj);

    bool validate() override;
    void execute() override;

private:
    string enemy; 
    Player *enemyPlayer;
};
