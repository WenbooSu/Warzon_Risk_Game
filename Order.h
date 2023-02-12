#pragma once

#include "Player.h"

#include <string>
#include <queue>

using namespace std;

class Order
{
public:
    //Constructors
    Order();
    Order(string player);
    ~Order();
    Order(const Order& theOrder);

    //Accessors
    string getPlayer();

    bool validate();
    void execute();

    friend ostream& operator << (ostream& out, const Order& o);

private:
    string player;//Player* player;
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
    Deploy(string player, string territory);
    ~Deploy();
    Deploy(const Deploy& deployObj);

    bool validate();
    void execute();

    friend ostream& operator << (ostream& out, const Deploy& d);

private:
    string territory; //Territory territory;
};

class Advance : public Order
{
public:
    //Constructors
    Advance();
    ~Advance();
    Advance(string player, string source_territory, string adjacent_territory);
    Advance(const Advance& advanceObj);

    bool validate();
    void execute();

private:
    string source_territory; //Territory source_territory;
    string adjacent_territory; //Territory adjacent_territory;
};

class Bomb : public Order
{
public:
    //Constructors
    Bomb();
    ~Bomb();
    Bomb(string player, string target);
    Bomb(const Bomb& bombObj);

    bool validate();
    void execute();

private:
    string target; //Territory target;
};

class Blockade : public Order
{
public:
    //Constructors
    Blockade();
    ~Blockade();
    Blockade(string player, string target);
    Blockade(const Blockade& blockadeObj);

    bool validate();
    void execute();

private:
    string target; //Territory target;
};

class Airlift : public Order
{
public:
    //Constructors
    Airlift();
    ~Airlift();
    Airlift(string player, string source, string target);
    Airlift(const Airlift& airliftObj);

    bool validate();
    void execute();

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
    Negotiate(string player, string enemy);
    Negotiate(const Negotiate& negotiateObj);

    bool validate();
    void execute();

private:
    string enemy; //Player enemy;
};
