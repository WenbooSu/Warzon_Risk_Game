#pragma once
#include <string>
#include <cstring>
using namespace std;

/*
* Abstract Base class
* Description: This is an abstract class that every state 
*              will inherit from.
*/
class State {
protected:
	const string* name;
	State* invalidCommmand();
public:
	string getName();
	//virtual void UpdateState() = 0;
	virtual State* Transition(string command) = 0;
};

/*
* Derived class
* Description: This state represents the starting point
*			   of the game, before rules are decided.
*/
class StateStart : public State {
private:
	~StateStart();
	const string* transition;
public:
	StateStart();
	State* Transition(string command);
};

/*
* Derived class
* Description: State where the user chooses to load a map
*/
class StateMapLoad : public State {
private:
	~StateMapLoad();
	const string* transitionLoad;
	const string* transitionValidate;
public:
	StateMapLoad();
	State* Transition(string command);
};

/*
* Derived class
* Description: After a map has loaded, this class validates
*			   the map chosen by the user.
*/
class StateMapValidate : public State {
private:
	~StateMapValidate();
	const string* transition;
public:
	StateMapValidate();
	State* Transition(string command);
};

/*
* Derived class
* Description: In this state, the number of players will be decided.
*			   This is the last state before the game begins.
*/
class StateAddPlayers : public State {
private:
	~StateAddPlayers();
	const string* transitionAdd;
	const string* transitionPlay;
public:
	StateAddPlayers();
	State* Transition(string command);
};

/*
* Derived class
* Description: The starting state of a round for the player.
*			   Here, the players assigns how many units go to 
*			   each territory they have captured.
*/
class StateAssign : public State {
private:
	~StateAssign();
	const string* transition;
public:
	StateAssign();
	State* Transition(string command);
};

/*
* Derived class
* Description: After assigning reinforcements,
			   new orders can be issued during the turn.
*/
class StateIssueOrders : public State {
private:
	~StateIssueOrders();
	const string* transitionIssueOrder;
	const string* transitionExecuteOrder;
public:
	StateIssueOrders();
	State* Transition(string command);
};

/*
* Derived class
* Description: In this state, after the orders were issued,
*			   the orders will come into effect.
*/
class StateExecuteOrders : public State {
private:
	~StateExecuteOrders();
	const string* transitionExecuteOrder;
	const string* transitionEndOrders;
	const string* transitionWin;
public:
	StateExecuteOrders();
	State* Transition(string command);
};
/*
* Derived class
* Description: After assigning reinforcements,
			   new orders can be issued during the turn.
*/
class StateWin : public State {
private:
	~StateWin();
	const string* transitionEnd;
	const string* transitionRestart;
public:
	StateWin();
	State* Transition(string command);
};

/*
* Base class
* Description: This class controls and manages the game states.
*/
class GameEngine {
private:
	State* currentState;

public:
	GameEngine();
	~GameEngine();
	/*bool isPlaying();*/
	string getStateName();
	void ChangeState(string command);
};