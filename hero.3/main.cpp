#include "Game.h"

int main()
{

	Game game(640, 480, "Hero");

	game.init();
	game.mainLoop();
	game.quit();

	return 0;
}