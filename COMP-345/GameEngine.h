#pragma once
#include <string>
#include <vector>
#include "MapLoader.h"
#include "Card.h"

using namespace std;

/*
* Abstract Base class
* Description: This is an abstract class that every state 
*              will inherit from.
*/
class State {
protected:
	const string* name;
	/*Default error message output.*/
	State* invalidCommmand();
public:
	/*Return the name of the state.*/
	string getName();
	/*Transition to state based on user input.*/
	virtual State* Transition(string command) = 0;
	Map* map;
};

class StartupPhaseState : public State {
public:
	virtual void Startup() = 0;
};

class PlayStatePhase : public State {

};

/*
* Derived class
* Description: This state represents the starting point
*			   of the game, before rules are decided.
*/
class StateStart : public StartupPhaseState {
private:
	~StateStart();
	const string* transition;
public:
	StateStart();
	State* Transition(string command);
	void Startup();
};

/*
* Derived class
* Description: State where the user chooses to load a map
*/
class StateMapLoad : public StartupPhaseState {
private:
	~StateMapLoad();
	const string* transitionLoad;
	const string* transitionValidate;
public:
	StateMapLoad();
	State* Transition(string command);
	void Startup();
	MapLoader* LoadMap(string map);
};

/*
* Derived class
* Description: After a map has loaded, this class validates
*			   the map chosen by the user.
*/
class StateMapValidate : public StartupPhaseState {
private:
	~StateMapValidate();
	const string* transition;
public:
	StateMapValidate();
	State* Transition(string command);
	void Startup();
	Map* map;
};

/*
* Derived class
* Description: In this state, the number of players will be decided.
*			   This is the last state before the game begins.
*/
class StateAddPlayers : public StartupPhaseState {
private:
	~StateAddPlayers();
	const string* transitionAdd;
	const string* transitionPlay;
public:
	StateAddPlayers();
	State* Transition(string command);
	void Startup();
};

/*
* Derived class
* Description: The starting state of a round for the player.
*			   Here, the players assigns how many units go to 
*			   each territory they have captured.
*/
class StateAssign : public PlayStatePhase {
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
class StateIssueOrders : public PlayStatePhase {
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
class StateExecuteOrders : public PlayStatePhase {
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
class StateWin : public PlayStatePhase {
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
	const string* const commandEnd = new string("end");
	State* currentState;
	string userCommand;
	MapLoader* map;
	vector<Player*> players;
	Deck* deck;
	void CommandSplit(string, string values[], int);

public:
	GameEngine();
	~GameEngine();
	/*Copy Constructor*/
	GameEngine(GameEngine& engine);
	/*Check if the game should continue based on user inputand state.*/
	bool isPlaying();
	/*Return the name of the current state*/
	string getStateName();
	/*Given user input, change or deny the state transition.*/
	bool ChangeState(string command);
	/*Call the startup method of the current state to commence it part of the startup phase.*/
	void StartupPhase();
	/*Compare name of this current state and parameter's.*/
	bool operator == (GameEngine* engine);
	/*Print the engine's current state.*/
	friend ostream& operator << (ostream&, const GameEngine&);
	/*Take input as a command.*/
	friend istream& operator >> (istream&, GameEngine&);
};