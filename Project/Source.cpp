#include "Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();
	game->StartGame();
	delete game;
	return 0;
}