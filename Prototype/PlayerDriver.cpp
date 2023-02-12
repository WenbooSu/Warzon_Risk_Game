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

    static vector<Territory*> TerritoryAll;
    TerritoryAll.push_back(tr1);
    TerritoryAll.push_back(tr2);
    TerritoryAll.push_back(tr3);
    TerritoryAll.push_back(tr4);
    TerritoryAll.push_back(tr5);
    TerritoryAll.push_back(tr6);
    TerritoryAll.push_back(tr7);
    TerritoryAll.push_back(tr8);
    TerritoryAll.push_back(tr9);

    vector<Territory*> TerritoryP1;
    TerritoryP1.push_back(tr1);
    TerritoryP1.push_back(tr2);
    TerritoryP1.push_back(tr3);
    TerritoryP1.push_back(tr4);
    TerritoryP1.push_back(tr5);

    vector<Territory*> TerritoryP2 ;
    TerritoryP2.push_back(tr5);
    TerritoryP2.push_back(tr6);
    TerritoryP2.push_back(tr7);
    TerritoryP2.push_back(tr8);

Player p1 = new Player("Yulong", TerritoryP1, vector<Card*> hand,vector<Order*> orderList);
Player p2 = new Player("Zach", TerritoryP2, vector<Card*> hand,vector<Order*> orderList);
}