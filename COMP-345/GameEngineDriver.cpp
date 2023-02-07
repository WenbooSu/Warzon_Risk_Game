#include <iostream>
#include "GameEngine.h"
using namespace std;

int main() {
	GameEngine engine;
	string command;
	//The main game loop. Continues endlessly, for now.
	//REMOVE MAGIC NUMBERS
	while (command != "end" || engine.getStateName() != "win") {
		cout << "Game Engine Driver." <<
		"\n\nCurrent Game State: " << engine.getStateName() <<
		"\nPlease enter your command:" << endl;
		cin >> command;
		//Before changing state, clear the screen.
		system("cls");
		engine.ChangeState(command);
	}
	return 0;
}