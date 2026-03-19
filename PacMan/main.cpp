#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	// 실행 성공 시 true를 받음
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}