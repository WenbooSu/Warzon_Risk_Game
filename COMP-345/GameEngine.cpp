#include <iostream>
#include "GameEngine.h"
using namespace std;

/*******************************
		State Class 
*******************************/
string State::getName() {
	return *name;
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
		cerr << "Error: invalid command entered.\n" << endl;
		return nullptr;
	}
}

/*******************************
	Map Load State Class
*******************************/
StateMapLoad::StateMapLoad() {
	this->name = new string("Map Load");
}

State* StateMapLoad::Transition(string command){
	return nullptr;
}

/*******************************
	Map Validate State Class
*******************************/


State* StateMapValidate::Transition(string command){
	return nullptr;
}

/*******************************
	Add Players State Class
*******************************/


State* StateAddPlayers::Transition(string command){
	return nullptr;
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