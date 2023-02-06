#include <iostream>
#include "GameEngine.h"
using namespace std;

int main() {
	Engine engine;
	string command;
	//The main game loop. Continues endlessly, for now.
	while (true){
		cout << "Game Engine Driver." <<
		"\n\nCurrent Game State: " << engine.getState()->getName() <<
		"\nPlease enter your command: " << endl;
		cin >> command;
		//Before changing state, clear the screen.
		system("cls");
		engine.ChangeState(command);
	}
	return 0;
}