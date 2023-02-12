#include <vector>
#include <string>
#include "Player.h"
#include "MapLoader.h"
#include<iostream>
using namespace std;

int main() 
{

    Territory tr1 = new Territory("North America", "Canada", 1287879);
    Territory tr2 = new Territory("North America", "USA", 1276768);
    Territory tr3 = new Territory("Europe", "Slovania", 12687879);
    Territory tr4 = new Territory("Asia", "China", 1254546);
    Territory tr5 = new Territory("Asia", "India", 1234345);
    Territory tr6 = new Territory("Asia", "Japan", 1231231);
    Territory tr7 = new Territory("Europe", "England", 1298080);
    Territory tr8 = new Territory("Europe", "Spain", 1234567);
    Territory tr9 = new Territory("Europe", "Portugual", 1212121);

    static vector<Territory*> territoryAll;
    territoryAll.push_back(tr1);
    territoryAll.push_back(tr2);
    territoryAll.push_back(tr3);
    territoryAll.push_back(tr4);
    territoryAll.push_back(tr5);
    territoryAll.push_back(tr6);
    territoryAll.push_back(tr7);
    territoryAll.push_back(tr8);
    territoryAll.push_back(tr9);

    vector<Territory*> territoryP1;
    territoryP1.push_back(tr1);
    territoryP1.push_back(tr2);
    territoryP1.push_back(tr3);
    territoryP1.push_back(tr4);
    territoryP1.push_back(tr5);

    vector<Territory*> territoryP2 ;
    territoryP2.push_back(tr5);
    territoryP2.push_back(tr6);
    territoryP2.push_back(tr7);
    territoryP2.push_back(tr8);

    vector<string*> handP1 = {"Bomb", "Reinforcement"}

    vector<string*> handP2= {"Airlift", "Diplomacy"}

    OrderTemp ot1 = new OrderTemp("Deploy");
    OrderTemp ot2 = new OrderTemp("Advance");
    OrderTemp ot3 = new OrderTemp("Bomb");
    OrderTemp ot4 = new OrderTemp("Airlift");

    vector<OrderTemp*> olP1;
    olP1.push_back(ot1);
    olP1.push_back(ot2);

    vector<OrderTemp*> olP2;
    olP1.push_back(ot3);
    olP1.push_back(ot4);

Player p1 = new Player("Yulong", territoryP1, handP1, olP1);
Player p2 = new Player("Zach", territoryP2, handP2, olP2);

std::cout p1;
std::cout p2;

p1.toAttack(p1.compareTerritoryList(territoryAll,p1.terriortyList));
p2.toAttack(p2.compareTerritoryList(territoryAll,p2.terriortyList));

p1.toDefend(p1.terriortyList);
p2.toDefend(p2.terriortyList);

p1.issueOrder("Deploy");
p2.issueOrder("Airlift");
}