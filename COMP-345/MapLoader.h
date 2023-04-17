//
// Created by Administrator on 2023/2/11.
//
#include <vector>
#include <string>
#include "Player.h"
#ifndef A1_MAPLOADER_H
#define A1_MAPLOADER_H
using namespace std;

class Territory
{
private:
    string continentID;
    string territoryName;
    Player* player;
    int armies;
    int territoryID;
    int weight;

public:
    Territory(); //default constructor
    Territory(string continentID, string territoryName, int countryID);
    Territory (string continentID, string territoryName, Player* player, int numArmies, int countryID);
    ~Territory(); //destructor
    string getContinentID(); //return the Continent that contains this territory
    string getTerritoryName(); //return the name of the territory
    Player* getPlayer(); //return the owner of the territory
    void setPlayer(Player*); //Set the owner of the territory
    int getArmies(); //return the number of military units on this territory
    int getTerritoryID();
    int getGraphWeight();
    void setGraphWeight();
    void setArmies(int a);
    void addArmies(int a);
};

class Continents
{
private:
    string continentName;
    int continentArmies;
    int continentID;
    int weight;

public:
    Continents();
    Continents(string name, int armies, int cid);
    ~Continents();
    string getContinentName();
    int getContinentArmiesUnits();
    int getContinentID();
    void setContinentWeight();
    int getContinentWeight();
};

class Map
{
private:
    //int vertices;
    string fileName;
    vector<vector<Territory>> matrix;
    vector<vector<Territory>> generateGraph(vector<Territory*> countries, string fileName);
    void DFS(int v, vector<bool> &visited, int size);
    void DFS4Continents(int v, vector<bool> &visited, int size, vector<vector<Continents>> cv2d);

public:
    Map();
    Map(vector<Territory*> countries, string fileName);
    Map(int numOfNodes);
    ~Map();
    void addEdge(int n, int m);
    void toString();
    bool validate();
    bool continentsValidate();
    void check4Continents(vector<Territory> vt, vector<Continents> vc);
    vector<vector<Territory>> getMatrix();
    vector<Territory*> countries;
};

class MapLoader
{
private:
    Map* map;
    string fileName;
    int getLineCount(string fileName, string a, string b);

public:
    MapLoader();
    MapLoader(string fileName);
    ~MapLoader();
    //int getLineCount(string fileName, string a, string b);
    vector<Continents> getContinentsFromMapFile();
    vector<Territory*> getCountriesFromMapFile();
    bool bonusContinent(Continents, vector<Territory*>);
    void assignArmies(vector<Continents> cv, vector<Territory> tv);
    void showMap();
    bool verifyMapFile();
    Map* getMap();
};


#endif //A1_MAPLOADER_H
