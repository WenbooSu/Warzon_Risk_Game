#include "GameEngine.h"

int main() {
	GameEngine engine;
	while (engine.getIsPlaying()) {
	/*	engine.startupPhase();
		engine.mainGameLoop();*/
		engine.endPhase();
	}
	return 0;
}