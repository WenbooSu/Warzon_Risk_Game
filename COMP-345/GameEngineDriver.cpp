#include <iostream>
#include "GamEngineDriver.h"
#include "GameEngine.h"

int main() {
	play();
	return 0;
}

void play() {
	GameEngine engine;
	string command;
	//The main game loop. Continues until the user inputs "end" and someone wins.
	while (engine.isPlaying()) {
		//Output the Game Engine Driver UI and the current state.
		cout << "Game Engine Driver.\n\n"
			<< engine;
		//Get input to change states.
		cin >> engine;
		//Before changing state, clear the screen.
		system("cls");
	}
}