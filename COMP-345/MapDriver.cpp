#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "MapLoader.h"

using namespace std;

int mapDriver() {
    //map.txt is Connected
    // WOW.map is Connected
    // brasil.map is Connected
    // brasil2.map is NOT Connected
    // terribleMap.map is NOT valid
    string fileName="map.txt";
    MapLoader maploader(fileName);

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

    Map map(v2, fileName);
    map.toString();

    cout<<endl<<"Assign Army Units to Countries based on Continents: "<<endl<<endl;
    maploader.assignArmies(v1,v2);

    cout<<endl<<"Verify Territories Graph (Indirect) is Connected or NOT: "<<endl<<endl;
    cout<<map.validate()<<endl<<endl;

    cout<<endl<<"Verify Continents as Sub Graph (Indirect) is Connected or NOT: "<<endl<<endl;
    cout<<map.continentsValidate()<<endl<<endl;

    cout<<endl<<"Verify Each Territory only Belongs to 1 Continent: "<<endl<<endl;
    map.check4Continents(v2,v1);
    return 0;
}
