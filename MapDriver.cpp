#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "MapLoader.h"
using namespace std;
int main() {
    MapLoader maploader("map.txt");

    maploader.verifyMapFile();

    vector<Continents> v1 = maploader.getContinentsFromMapFile();
    vector<Territory> v2 = maploader.getCountriesFromMapFile();

    cout<<"Show All Continents"<<endl<<endl;
    for(int i=0; i<v1.size(); i++)
    {
        cout<<v1[i].getContinentID()<<" "<<v1[i].getContinentName()<<" "<<v1[i].getContinentArmiesUnits()<<endl;
    }

    cout<<endl<<"Show All Countries"<<endl<<endl;
    for(int i=0; i<v2.size(); i++)
    {
        cout<<v2[i].getTerritoryID()<<" "<<v2[i].getTerritoryName()<<" "<<v2[i].getContinentID()<<endl;
    }

    Map map(v2, "map.txt");
    map.toString();

    cout<<endl<<"Assign Army Units to Countries based on Continents: "<<endl<<endl;
    maploader.assignArmies(v1,v2);

    cout<<endl<<"Verify Territories Graph (Indirect) is Connected: "<<endl<<endl;
    cout<<map.validate()<<endl<<endl;

    return 0;
}
