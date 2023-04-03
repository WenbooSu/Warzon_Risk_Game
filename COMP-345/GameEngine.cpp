#include <iostream>
#include <conio.h>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <random>
#include "GameEngine.h"
using namespace std;

/*******************************
		State Class
*******************************/
string State::getName() {
	return *name;
}

State* State::invalidCommmand() {
	cerr << "Error: invalid command entered for " << *this->name << " state.\n\n" << endl;
	return nullptr;
}

/*******************************
	State Start Class
*******************************/
StateStart::StateStart() {
	//Upon instantiation, set name and command to transition state.
	this->name = new string("Start");
	this->transition = new string("loadmap");
}

StateStart::~StateStart() {
	delete this->name;
	delete this->transition;
}

State* StateStart::Transition(string command) {
	//Verify that the command meets the string to transition, otherwise error.
	if (command.compare(*this->transition) == 0) {
		return new StateMapLoad();
	}
	else {
		return this->invalidCommmand();
	}
}

void StateStart::Startup() {
	//Display a list of maps for the user.

}

/*******************************
	Map Load State Class
*******************************/
StateMapLoad::StateMapLoad() {
	//Upon instantiation, set name and command to both transition states.
	this->name = new string("Map Load");
	this->transitionLoad = new string("loadmap");
	this->transitionValidate = new string("validatemap");
}

StateMapLoad::~StateMapLoad() {
	delete this->name;
	delete this->transitionLoad;
	delete this->transitionValidate;
}


State* StateMapLoad::Transition(string command) {
	//Verify that the command meets the string to one of the transitions, otherwise error.
	if (command.compare(*this->transitionLoad) == 0) {
		return new StateMapLoad();
	}
	else if (command.compare(*this->transitionValidate) == 0) {
		return new StateMapValidate();
	}
	else {
		return this->invalidCommmand();
	}
}

MapLoader* StateMapLoad::LoadMap(string mapName) {
	MapLoader* mapLoader = new MapLoader();
	//Path to directory with map files.
	string path = "../";
	//Look through each file in the directory for a matching name.
	for (filesystem::directory_entry file : filesystem::directory_iterator(path)) {
		string fileName = file.path().string();
		fileName = fileName.substr(1, fileName.size() - 1);
		//If mach found, return the map loader, with the file name.
		if (fileName.compare("./" + mapName) == 0) {
			mapLoader = new MapLoader(path + fileName);
			return mapLoader;
		}
	}
	//Otherwise, return null pointer to indicate nothing found.
	return nullptr;
}

/*Use the loadmap <filename> command to select a map from a list of maps.*/
void StateMapLoad::Startup() {
	//Display a list of maps for the user.

	//Get the map files from the current directory.
	string path = "./";
	/*for(filesystem::directory_entry file : filesystem::directory_iterator(path)) {
		cout << file.path();
	}*/
}

/*******************************
	Map Validate State Class
*******************************/
StateMapValidate::StateMapValidate() {
	//Upon instantiation, set name and command to transition state.
	this->name = new string("Map Validated");
	this->transition = new string("addplayer");
	this->map = nullptr;
}

StateMapValidate::~StateMapValidate() {
	delete this->name;
	delete this->transition;
	delete this->map;
}

State* StateMapValidate::Transition(string command) {
	//Verify that the command meets the string to transition, otherwise error.
	if (command.compare(*this->transition) == 0) {
		return new StateAddPlayers();
	}
	else {
		return this->invalidCommmand();
	}
}

void StateMapValidate::Startup() {

}

/*******************************
	Add Players State Class
*******************************/
StateAddPlayers::StateAddPlayers() {
	//Upon instantiation, set name and command to both transition states.
	this->name = new string("Players Added");
	this->transitionAdd = new string("addplayer");
	this->transitionPlay = new string("gamestart");
}

StateAddPlayers::~StateAddPlayers() {
	delete this->name;
	delete this->transitionAdd;
	delete this->transitionPlay;
}

State* StateAddPlayers::Transition(string command) {
	//Verify that the command meets the string to one of the transitions, otherwise error.
	if (command.compare(*this->transitionAdd) == 0) {
		return new StateAddPlayers();
	}
	else if (command.compare(*this->transitionPlay) == 0) {
		return new StateAssign();
	}
	else {
		return this->invalidCommmand();
	}
}

void StateAddPlayers::Startup() {

}

/************************************
  Assign Reinforcements State Class
************************************/
StateAssign::StateAssign() {
	//Upon instantiation, set name and command to its transition state.
	this->name = new string("Assign Reinforcement");
	this->transition = new string("issueorder");
}

StateAssign::~StateAssign() {
	delete this->name;
	delete this->transition;
}

State* StateAssign::Transition(string command) {
	//Verify that the command meets transition string, otherwise error.
	if (command.compare(*this->transition) == 0) {
		return new StateIssueOrders();
	}
	else {
		return this->invalidCommmand();
	}
}

/*******************************
	Issue Orders State Class
*******************************/
StateIssueOrders::StateIssueOrders() {
	//Upon instantiation, set name and commands to both transition states.
	this->name = new string("Issue Orders");
	this->transitionIssueOrder = new string("issueorder");
	this->transitionExecuteOrder = new string("endissueorders");
}
StateIssueOrders::~StateIssueOrders() {
	delete this->name;
	delete this->transitionIssueOrder;
	delete this->transitionExecuteOrder;
}

State* StateIssueOrders::Transition(string command) {
	//Verify that the command meets the string to one of the transitions, otherwise error.
	if (command.compare(*this->transitionIssueOrder) == 0) {
		return new StateIssueOrders();
	}
	else if (command.compare(*this->transitionExecuteOrder) == 0) {
		return new StateExecuteOrders();
	}
	else {
		return this->invalidCommmand();
	}
}

/*********************************
	Execute Orders State Class
*********************************/
StateExecuteOrders::StateExecuteOrders() {
	//Upon instantiation, set name and commands to its transition states.
	this->name = new string("Execute Orders");
	this->transitionExecuteOrder = new string("execorder");
	this->transitionEndOrders = new string("endexecorders");
	this->transitionWin = new string("win");
}

StateExecuteOrders::~StateExecuteOrders() {
	delete this->name;
	delete this->transitionExecuteOrder;
	delete this->transitionEndOrders;
	delete this->transitionWin;
}

State* StateExecuteOrders::Transition(string command) {
	//Verify that the command meets the string to one of the transitions, otherwise error.
	if (command.compare(*this->transitionExecuteOrder) == 0) {
		return new StateExecuteOrders();
	}
	else if (command.compare(*this->transitionEndOrders) == 0) {
		return new StateAssign();
	}
	else if (command.compare(*this->transitionWin) == 0) {
		return new StateWin();
	}
	else {
		return this->invalidCommmand();
	}
}

/*******************************
		Win State Class
*******************************/
StateWin::StateWin() {
	//Upon instantiation, set name and commands to both transition states.
	this->name = new string("Win");
	this->transitionEnd = new string("end");
	this->transitionRestart = new string("play");
}

StateWin::~StateWin() {
	delete this->name;
	delete this->transitionEnd;
	delete this->transitionRestart;
}

State* StateWin::Transition(string command) {
	//Verify that the command meets the string to one of the transitions, otherwise error.
	if (command.compare(*this->transitionEnd) == 0) {
		return nullptr;
	}
	else if (command.compare(*this->transitionRestart) == 0) {
		return new StateStart();
	}
	else {
		return this->invalidCommmand();
	}
}

/*******************************
		Engine Class
*******************************/
GameEngine::GameEngine() {
	this->currentState = new StateStart();
	this->map = nullptr;
	this->deck = new Deck();
}

GameEngine::GameEngine(GameEngine& engine) {
	this->currentState = engine.currentState;
	this->map = nullptr;
	this->deck = new Deck();
}

GameEngine::~GameEngine() {
	delete this->commandEnd;
	delete this->currentState;
	delete this->map;
	//Go through each play in the instance's player vector and delete them.
	for (Player* p : this->players) {
		delete p;
	}
	delete this->deck;
}

bool GameEngine::isPlaying() {
	/*Check if the command matches the end game command, and
	  whether the current state can be converted to win state, if not, the current state is already win state.*/
	return this->userCommand.compare(*this->commandEnd) != 0 || dynamic_cast<StateWin*>(currentState) == nullptr;
}

string GameEngine::getStateName() {
	return this->currentState->getName();
}

bool GameEngine::ChangeState(string command) {
	//Store the user's input.
	this->userCommand = command;
	//Get the next state from the current state based on user input.
	State* s = this->currentState->Transition(command);
	//If a valid State object was returned, delete the curent and replace it with new one.
	if (s != NULL) {
		delete this->currentState;
		this->currentState = s;
		return true;
	}
	return false;
}

void GameEngine::StartupPhase() {
	string input = "";
	bool validMap = false;
	const int numCommands = 2;
	const int minPlayers = 2;
	const int maxPlayers = 6;
	int numPlayers = 0;
	//Loop until the startup phase has been completed.
	while (dynamic_cast<StateAssign*>(this->currentState) == nullptr) {
		cout << "\n\nState: " << this->currentState->getName() << endl;
		cout << "Please enter a command" << endl;
		//Get the user's command and input.
		getline(cin, input);
		//Split the string: first is the command, second is any input such as map name or player name.
		string commands[numCommands];
		CommandSplit(input, commands, numCommands);
		//If possible, change state, and capture the result.
		bool validCommand = this->ChangeState(commands[0]);
		//Based on changed state changed to, do correspoinding part of the startup phase.
		if (StateMapLoad* s = dynamic_cast<StateMapLoad*>(this->currentState); s != nullptr && validCommand) {
			this->map = s->LoadMap(commands[1]);
			//If the map does not exist in the directory, do not allow user to proceed to validate map state.
			validMap = this->map == nullptr ? false : true;
			if (validMap) {
				this->map->showMap();
			}
		}
		if (StateMapValidate* s = dynamic_cast<StateMapValidate*>(this->currentState); s != nullptr && validCommand && validMap) {
			//If the map is invalid, stay in the map load state.
			if (!this->map->verifyMapFile()) {
				this->currentState = new StateMapLoad();
			}
		}
		//If the map in load state is invalid, inform the user and stay in load map state.
		else if (!validMap) {
			cout << "Please enter a valid map." << endl;
			this->currentState = new StateMapLoad();
		}
		if (dynamic_cast<StateAddPlayers*>(this->currentState) != nullptr && validCommand) {
			//Given a name, create a new player, and add them to the vector of players. Minimum 2, max of 6.
			if (numPlayers < maxPlayers) {
				numPlayers++;
				Player* player = new Player();
				player->setName(commands[1]);
				cout << player->getName() << endl;
				this->players.push_back(player);
			}
			else {
				cout << "Maximum of 6 players, no more can be added." << endl;
			}
		}
		//When attempting to end startup phase, check that there are ewnough players, if not, stay in add players state.
		if (dynamic_cast<StateAssign*>(this->currentState) != nullptr && numPlayers < minPlayers) {
			cout << "Minimum of 2 players needed. There're currently: " + numPlayers << endl;
			this->currentState = new StateAddPlayers();
		}
	}
	//At the end of the startup phase, after adding players, start by setting up the deck of cards.
	const int numCards = 2 * numPlayers;
	this->deck->createDeck(numCards);
	//Begin by distributing the territories to players.
	vector<Territory*> territories = this->map->countries;
	int numTerritoriesPerPlayer = territories.size() / numPlayers;
	Player* player = this->players[0];
	int j = 0;
	for (int i = 0; i < (numTerritoriesPerPlayer * numPlayers); i++) {
		if (i % numTerritoriesPerPlayer == 0 && i != 0) {
			player = this->players[++j];
		}
		//Add the territory to the player's list of territories.
		Territory* t = territories[i];
		player->addTerritory(t);
		//Assign the player pointer to the territory.
		t->setPlayer(player);
		cout << "Player: " + player->getName() << "\tAdded: " + t->getTerritoryName() << endl;
	}
	player = nullptr;
	//Determine random play order.
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(this->players.begin(), this->players.end(), mt);
	const int armiesStart = 50;
	for (Player* player : this->players) {
		cout << "Player: " + player->getName() << endl;
		//Give each player 50 armies initially to their reinforcement pool.
		player->addArmies(armiesStart);
		cout << "Added initial " << player->getArmies() << " armies to player" << endl;
		//Let each playe draw 2 cards from the deck.
		player->addToHand(this->deck->draw());
		player->addToHand(this->deck->draw());
		cout << "The following cards have been added to their hand: " << endl;
		player->getHand()->showHand();
		cout << endl;
	}
}

void GameEngine::mainGameLoop() {
	//If the no one has won the game, continue the main game loop.
	while (dynamic_cast<StateWin*>(currentState) == nullptr) {
		//Begin each cycle of the main game loop with the reinforcement phase.
		this->reinforcementPhase();
		this->ChangeState("issueorder");
		//Now, for each player, in order, allow them them to issue orders.
		this->issueOrdersPhase();
		//Once all the orders have been issued, execute them in round robin fashion.
		this->executeOrdersPhase();
		//Verify that each player controls at least one territory, if not, remove them from the game.
		for (int i = 0; i < this->players.size(); i++) {
			if (this->players[i]->getTerritoryList().size() < 1) {
				this->players.erase(this->players.begin() + i);
			}
		}
	}
}

void GameEngine::reinforcementPhase() {
	double basicReinforcement;
	double controlBonus;
	double totalArmiesAdded;
	//For each player, add their respective number of armies based on territories owned.
	cout << "This is the reinforcement phase and the player will be given a number of armies\n" << endl;
	for (Player* player : this->players) {
		basicReinforcement = floor(player->getTerritoryList().size() / 3);
		controlBonus = 0;
		/*
		
		
		
		Determine bonus armies.




		*/
		//By default, no matter how many territories owned, a player will receive three armies.
		if (basicReinforcement < 3) {
			basicReinforcement = 3;
		}
		totalArmiesAdded = basicReinforcement + controlBonus;
		cout << "For player: " + player->getName() << endl;
		cout << "Player's control bonus = " << controlBonus << endl;
		cout << "Player's basic reinforcement = " << basicReinforcement << endl;;
		cout << "The player will now receive " << totalArmiesAdded << " armies" << endl;;
		player->addArmies(totalArmiesAdded);
	}
}

void GameEngine::issueOrdersPhase() {
	for (Player* player : this->players) {
		player->issueOrder(this->deck, this->players, this->map);
	}
}


void GameEngine::executeOrdersPhase() {
	int playesOrdersDone = 0;
	//Reset number of players done every iteration, keep iterating until all players are done.
	while (playesOrdersDone < this->players.size()) {
		playesOrdersDone = 0;
		int i = 0;
		for (Player* player : this->players) {
			if (player->getOrderList()->getList().size() > 0) {
				//If it is not empty, get the front element.
				Order* order = player->getOrderList()->getList()[0];
				//Since the order list is like a queue, remove the first element, and then execute it
				player->getOrderList()->remove(0);
				order->execute();
			}
			else {
				//If that player no longer has orders to execute, count them as done.
				playesOrdersDone++;
			}
		}
		i++;
	}
}

bool GameEngine::operator==(GameEngine* engine) {
	return this->getStateName() == engine->getStateName();
}

ostream& operator<<(ostream& output, const GameEngine& engine) {
	output << "Game Engine's current state: " << engine.currentState->getName();
	return output;
}

istream& operator>>(istream& input, GameEngine& engine) {
	string command;
	input >> command;
	engine.ChangeState(command);
	return input;
}

void GameEngine::CommandSplit(string command, string values[], const int num) {
	stringstream stream(command);
	string s;
	for (int i = 0; i < num; i++) {
		getline(stream, s, ' ');
		values[i] = s;
	}
}