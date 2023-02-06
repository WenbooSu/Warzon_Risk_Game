#pragma once
#include <string>
#include <cstring>
using namespace std;

/*
* Base class
* Description: This is an abstract class that every state 
*              will inherit from.
*/
class State {
protected:
	const string* name;
public:
	string getName();
	virtual void UpdateState() = 0;
	virtual State* Transition(string command) = 0;
};

/*
* Abstract class
* Description: This state represents the starting point
*			   of the game, before rules are decided.
*/
class StateStart : public State {
private:
	~StateStart();
	const string* transition;
public:
	StateStart();
	void UpdateState();
	State* Transition(string command);
};

/*
* Abstract class
* Description: State where the user chooses to load a map
*/
class StateMapLoad : public State {
public:
	StateMapLoad();
	void UpdateState();
	State* Transition(string command);
};

/*
* Base class
* Description: After a map has loaded, this class validates
*			   the map chosen by the user.
*/
class StateMapValidate : public State {
public:
	StateMapValidate();
	void UpdateState();
	State* Transition(string command);
};

/*
* Base class
* Description: In this state, the number of players will be decided.
*			   This is the last state before the game begins.
*/
class StateAddPlayers : public State {
public:
	StateAddPlayers();
	void UpdateState();
	State* Transition(string command);
};

/*
* Base class
* Description: This class controls and manages the game states.
*/
class Engine {
private:
	State* currentState;

public:
	Engine();
	~Engine();
	State* getState();
	void ChangeState(string command);
};