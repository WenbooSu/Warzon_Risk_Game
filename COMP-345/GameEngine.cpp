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
		return nullptr;
	}
	else {
		return this->invalidCommmand();
	}
}

/*******************************
		Engine Class
*******************************/
Engine::Engine() {
	currentState = new StateStart();
}

Engine::~Engine() {
	delete currentState;
}

State* Engine::getState() {
	return this->currentState;
}

void Engine::ChangeState(string command) {
	//Get the next state from the current state based on user input.
	State * s = this->currentState->Transition(command);
	if (s != NULL) {
		delete currentState;
		currentState = s;
	}
}