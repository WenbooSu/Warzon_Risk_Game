#include "GameEngine.h"

int main() {
	GameEngine engine;
	engine.StartupPhase();
	engine.mainGameLoop();
	return 0;
}