#include "GameEngine.h"

int main() {
	GameEngine engine;
	//vector<int> v;
	//v.push_back(1);
	//v.push_back(2);
	//v.push_back(3);
	//int* i = &v[0];
	//cout << *i << endl;
	//v.erase(v.begin());
	//cout << *i << endl;
	engine.StartupPhase();
	engine.mainGameLoop();
	return 0;
}