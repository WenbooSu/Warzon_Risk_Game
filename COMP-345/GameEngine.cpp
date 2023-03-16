#include <iostream>
#include <conio.h>
#include <filesystem>
#include <sstream>
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

State* StateStart::Transition(string command){
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


State* StateMapLoad::Transition(string command){
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

Map* StateMapLoad::LoadMap(string name) {
	//Get the map files from the current directory.
	string path = "../";
	cout << path + name  << endl;
	for (filesystem::directory_entry file : filesystem::directory_iterator(path)) {
		cout << file << endl;
	}
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

State* StateMapValidate::Transition(string command){
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

State* StateAddPlayers::Transition(string command){
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
}

GameEngine::GameEngine(GameEngine& engine) {
	this->currentState = engine.currentState;
	this->map = nullptr;
}

GameEngine::~GameEngine() {
	delete this->currentState;
	delete this->map;
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
	State * s = this->currentState->Transition(command);
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
	//Loop until the startup phase has been completed.
	while (dynamic_cast<StateAssign*>(this->currentState) == nullptr) {
		cout << "State: " << this->currentState->getName() << endl;
		cout << "Please enter a command" << endl;
		//Get the user's command.
		getline(cin, input);
		//Split the string: first is the command, second is any input such as map name or player name.
		const int numCommands = 2;
		string commands[numCommands];
		CommandSplit(input, commands, numCommands);
		//If possible, change state, and captrue the result.
		bool validaCommand = this->ChangeState(commands[0]);
		//Based on changed state changed to, do correspoinding part of the startup phase.
		if (StateMapLoad* s = dynamic_cast<StateMapLoad*>(this->currentState); s != nullptr && validaCommand) {
			//Given the name of teh map from the command, load it and store it in the game engine.
			this->map = s->LoadMap(commands[1]);
		}
		if (StateMapValidate* s = dynamic_cast<StateMapValidate*>(this->currentState); s != nullptr && validaCommand) {
			this->map->validate();
		}
		if (dynamic_cast<StateAddPlayers*>(this->currentState) != nullptr && validaCommand) {
		
		}
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