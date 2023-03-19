//
// Created by Administrator on 2023/2/11.
//
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "MapLoader.h"

/*Player::Player() {


}*/

Continents::Continents() {
    this->continentName="none";
    this->continentArmies=0;
    this->continentID=-1;
    this->weight=0;
}

Continents::Continents(std::string name, int armies, int cid) {
    this->continentName=name;
    this->continentArmies=armies;
    this->continentID=cid;
    this->weight=0;
}

Continents:: ~Continents() {


}

string Continents::getContinentName() {
    return this->continentName;
}

int Continents::getContinentArmiesUnits() {
    return this->continentArmies;
}

int Continents::getContinentID() {
    return this->continentID;
}

int Continents::getContinentWeight() {
    return this->weight;
}

void Continents::setContinentWeight() {
    this->weight=1;
}

Territory::Territory() {
    continentID=-1;
    territoryName="null";
    player= nullptr;
    armies=0;
    weight=0;
}



Territory::Territory(std::string continentID, std::string territoryName, int countryID) {
    this->continentID=continentID;
    this->territoryName=territoryName;
    this->territoryID=countryID;
    this->weight=0;
}

Territory::Territory(std::string continentID, std::string territoryName, Player *player, int numArmies, int countryID) {
    this->continentID=continentID;
    this->territoryName=territoryName;
    this->territoryID=countryID;
    this->player=player;
    this->armies=numArmies;
    this->weight=0;
}

Territory::~Territory() {

}

string Territory::getContinentID() {
    return this->continentID;
}

string Territory::getTerritoryName() {
    return this->territoryName;
}

int Territory::getArmies() {
    return this->armies;
}

int Territory::getTerritoryID() {
    return this->territoryID;
}

int Territory::getGraphWeight() {
    return this->weight;
}

void Territory::setGraphWeight() {
    this->weight=1;
}

void Territory::setArmies(int a) {
    this->armies=a;
}

void Territory::addArmies(int a) {
    this->armies += a;
}

Player* Territory::getPlayer() {
    return this->player;
}

void Territory::setPlayer(Player* player) {
    this->player = player;
}

Map::Map() {

}

Map::~Map() {

}


Map::Map(vector<Territory> countries, string fileName) {
    matrix=this->generateGraph(countries, fileName);
    this->fileName=fileName;
}

void Map::addEdge(int n, int m) {
    this->matrix[n][m].setGraphWeight();
    this->matrix[m][n].setGraphWeight();
}

vector<vector<Territory>>  Map::generateGraph(vector<Territory> countries, string fileName) {
    vector<vector<Territory>> temp2DVector (countries.size(), countries);
    ifstream inStream;
    inStream.open(fileName);
    if(!inStream.is_open())
    {
        cout << "Fail to Open";
        exit(-1);
    }
    while(!inStream.eof())
    {
        string line;
        getline(inStream,line);
        if(line=="[borders]")
        {
            string line2;
            getline(inStream,line2);
            cout <<line2<<endl;
            while(!inStream.eof())
            {
                istringstream ss (line2);
                string head;
                ss >> head;
                cout <<"Country ID "<<head<<" has borders with:"<<endl;
                int row = (atoi(head.c_str())-1);
                string word;
                while (ss >> word)
                {
                    cout << word<< " ";
                    int col = (atoi(word.c_str())-1);
                    //cout<<"[row] [col] is "<<row<<" "<<col<<endl;
                    cout << temp2DVector[row][col].getTerritoryName()<<endl;
                    //cout<<"good program"<<endl;
                    temp2DVector[row][col].setGraphWeight();
                }
                cout << endl;
                getline(inStream,line2);
            }
        }
    }
    return temp2DVector;
}

void Map::DFS(int v, vector<bool> &visited, int size) {
    visited[v]=true;
    for(int i=0; i<size; i++)
    {
        if(matrix[v][i].getGraphWeight()==1 && !visited[i])
        {
            DFS(i, visited, size);
        }
    }
}

bool Map::validate() {
    // verify territories are connected
    vector<bool> visited(matrix.size(), false);
    DFS(0,visited,matrix.size());
    for(int i=0; i<matrix.size(); i++)
    {
        if(!visited[i])
        {
            return false;
        }
    }
    // verify continents are connected

    return true;
}

void Map::DFS4Continents(int v, vector<bool> &visited, int size, vector<vector<Continents>> cv2d) {
    visited[v]=true;
    for(int i=0; i<size; i++)
    {
        if(cv2d[v][i].getContinentWeight()==1 && !visited[i])
        {
            DFS4Continents(i,visited,size,cv2d);
        }
    }
}

bool Map::continentsValidate() {
    bool x = validate();
    //cout<<"x is "<<x<<endl;
    if(x)
    {
        MapLoader obj(this->fileName);
        vector<Continents> cv = obj.getContinentsFromMapFile();
        vector<vector<Continents>> cv2d (cv.size(), cv);
        /*cout<<"error check here"<<endl;
        for(int i=0; i<cv2d.size(); i++)
        {
            for(int j=0; j<cv2d.size(); j++)
            {
                cout<<cv2d[i][j].getContinentWeight();
            }
            cout<<endl;
        }*/
        for(int i=0; i<matrix.size(); i++)
        {
            for(int j=0; j<matrix.size(); j++)
            {
                if(matrix[i][j].getGraphWeight()==1)
                {
                    cv2d[atoi((matrix[i][j].getContinentID()).c_str())-1][atoi((matrix[j][i].getContinentID()).c_str())-1].setContinentWeight();
                    //cv2d[j][i].setContinentWeight();
                }
            }
        }
        /*cout<<"error check here"<<endl;
        for(int i=0; i<cv2d.size(); i++)
        {
            for(int j=0; j<cv2d.size(); j++)
            {
                cout<<cv2d[i][j].getContinentWeight()<<" ";
            }
            cout<<endl;
        }*/
    vector<bool> visited (cv2d.size(), false);
        DFS4Continents(0,visited,cv2d.size(),cv2d);
        for(int i=0; i<cv2d.size(); i++)
        {
            if(!visited[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

void Map::check4Continents(vector<Territory> vt, vector<Continents> vc) {
    for(int i=0; i<vt.size(); i++)
    {
        cout<<"Territory "<<vt[i].getTerritoryName()<<" belongs to ";
        int id = atoi(vt[i].getContinentID().c_str())-1;
        cout<<vc[id].getContinentName()<<endl;
    }
    cout<<endl<<"Each Territory only and can only belong to 1 Continent";
}

void Map::toString() {
    for(int i=0; i<matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            cout<<matrix[i][j].getGraphWeight()<<" ";
        }
        cout<<endl;
    }
}

MapLoader::MapLoader() {

}

MapLoader::~MapLoader() {

}

MapLoader::MapLoader(string fileName) {
    this->fileName = fileName;
    vector<Territory> countries = this->getCountriesFromMapFile();
    this->map = Map(countries, fileName); //map creates here
    this->map.toString();
}

vector<Continents> MapLoader::getContinentsFromMapFile() {
    vector<Continents> continents;
    ifstream inStream;
    inStream.open(fileName);
    if(!inStream.is_open())
    {
        cout << "Fail to Open";
        exit(-1);
    }
    while(!inStream.eof())
    {
        string line;
        getline(inStream, line);
        if(line=="[continents]")
        {
            string continentLine;
            getline(inStream, continentLine);
            int count = 0;
            while(continentLine!="[countries]" && continentLine!=" ")
            {
                istringstream ss (continentLine);
                string word1, word2;
                ss >> word1;
                ss >> word2;
                Continents continent (word1, atoi(word2.c_str()), (count+1));
                //vector<Continents>:: iterator it;
                continents.push_back(continent);
                count++;
                getline(inStream, continentLine);
                if(continentLine.empty())
                {
                    getline(inStream, continentLine);
                }
            }
        }
    }
    return continents;
}

vector<Territory> MapLoader::getCountriesFromMapFile() {
    cout <<"calling the function"<<endl;
    vector<Territory> terrorities;
    ifstream inStream;
    inStream.open(fileName);
    if(!inStream.is_open())
    {
        cout << "Fail to Open";
        exit(-1);
    }
    while(!inStream.eof())
    {
        string line;
        getline(inStream, line);
        if(line=="[countries]")
        {
            string line2;
            getline(inStream, line2);
            int count = 0;
            while(line2!="[borders]")
            {
                istringstream ss (line2);
                string word1, word2, word3;
                ss >> word1;//country id
                ss >> word2;//country name
                ss >> word3;//continent id
                //cout << "word 2 is"<<word1<<endl;
                //Continents continent (word1, atoi(word2.c_str()), (count+1));
                Territory terrority (word3, word2, atoi(word1.c_str()));
                //vector<Continents>:: iterator it;
                terrorities.push_back(terrority);
                count++;
                getline(inStream, line2);
                if(line2.empty())
                {
                    getline(inStream, line2);
                }
            }
        }
    }
    inStream.close();
    return terrorities;
}

void MapLoader::assignArmies(vector<Continents> cv, vector<Territory> tv) {
    for(int i=0; i<tv.size(); i++)
    {
        int continentID= atoi((tv[i].getContinentID()).c_str());
        int numArmies=cv[(continentID-1)].getContinentArmiesUnits();
        tv[i].setArmies(numArmies);
        cout << tv[i].getTerritoryName()<<" has armies of "<<tv[i].getArmies()<<endl;
    }
}

void MapLoader::showMap() {
    map.toString();
}

int MapLoader::getLineCount(std::string fileName, std::string a, std::string b) {
    int count=0;
    ifstream inStream;
    inStream.open(fileName);
    if(!inStream.is_open())
    {
        cout << "Fail to Open";
        exit(-1);
    }
    while(!inStream.eof())
    {
        string line;
        getline(inStream, line);
        if(line==a)
        {
            string line2;
            getline(inStream, line2);
            while (line2!=b && line2!=" ")
            {
                count++;
                getline(inStream, line2);
            }
        }
    }
    inStream.close();
    return (count-1);
}

bool MapLoader::verifyMapFile() {
    int count=0;
    int a=0;
    int b=0;
    int c=0;
    string line;
    string continent="[continents]";
    string countries="[countries]";
    string borders="[borders]";
    ifstream inStream;
    inStream.open(fileName);
    if (inStream.is_open()) {
        while (getline(inStream, line))
        {
            if (line.find(continent) != string::npos)
            {
                cout << "Found " << continent << " from file "<< endl;
                cout << "There are "<<getLineCount(fileName,continent,countries)<<" Continents"<<endl;
                a=1;
            }
            if(line.find(countries) != string::npos)
            {
                cout << "Found " << countries << " from file "<< endl;
                cout << "There are "<<getLineCount(fileName,countries,borders)<<" Countries"<<endl;
                b=1;
            }
            if(line.find(borders) != string::npos)
            {
                string line2;
                while(!inStream.eof())
                {
                    count++;
                    getline(inStream,line2);
                }
                cout << "Found " << borders << " from file " << endl;
                cout << "There are "<<(count-1)<<" Countries have Borders"<<endl;
                c=1;
            }
        }
        inStream.close();
    }
    if(a==b && a==c && b==c)
    {
        cout<< "The Map File is Valid"<<endl;
        return true;
    }
    else
    {
        cout<< "The Map File is NOT Valid"<<endl;
        return false;
    }
}