#include <iostream>
#include "GameEngine.h"
using namespace std;

/*******************************
		State Class 
*******************************/
string State::getName() {
	return *name;
}

State* State::invalidCommmand() {
	cerr << "Error: invalid command entered for " << *this->name << " state\n" << endl;
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

/*******************************
	Map Validate State Class
*******************************/
StateMapValidate::StateMapValidate() {
	//Upon instantiation, set name and command to transition state.
	this->name = new string("Map Validated");
	this->transition = new string("addplayer");
}

StateMapValidate::~StateMapValidate() {
	delete this->name;
	delete this->transition;
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

/*******************************
	Add Players State Class
*******************************/
StateAddPlayers::StateAddPlayers() {
	//Upon instantiation, set name and command to both transition states.
	this->name = new string("Players Added");
	this->transitionAdd = new string("addplayer");
	this->transitionPlay = new string("assigncountries");
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
	currentState = new StateWin();
}

GameEngine::GameEngine(GameEngine& engine) {
	this->currentState = engine.currentState;
}

GameEngine::~GameEngine() {
	delete currentState;
}

bool GameEngine::isPlaying() {
	/*Check if the command matches the end game command, and
	  whether the current state can be converted to win state, if not, the current state is already win state.*/
	return this->userCommand.compare(*this->commandEnd) != 0 || dynamic_cast<StateWin*>(currentState) == nullptr;
}

string GameEngine::getStateName() {
	return this->currentState->getName();
}

void GameEngine::ChangeState(string command) {
	//Get the next state from the current state based on user input.
	State * s = this->currentState->Transition(command);
	//If a valid State object was returned, delete the curent and replace it with new one.
	if (s != NULL) {
		delete currentState;
		currentState = s;
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
	cout << "\nPlease enter your command:" << endl;
	input >> engine.userCommand;
	engine.ChangeState(engine.userCommand);
	return input;
}