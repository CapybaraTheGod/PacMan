#include "Game.h"

// 생성자
Game::Game()
	: mWindow(nullptr)
	, mIsRunning(true)
{
}

// 초기화
bool Game::Initialize()
{
}

// 런 루프
void Game::RunLoop()
{
	// mIsRunning이 true인 동안 루프를 계속 돌림
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

// 셧다운
void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

// 입력 처리
void Game::ProcessInput()
{
	SDL_Event event;
	// 큐에 이벤트가 여전히 남아 있는 동안
	while (SDL_PollEvent(&event))
	{
		// 여러 유형의 이벤트를 다룸
		switch (event.type)
		{
		// 사용자가 화면 X키 또는 종료 단축키를 누른 경우
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// 키보드의 입력 상태 얻기
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// 이스케이프 키를 눌렀다면 루프 종료
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

// 게임 업데이트
void Game::UpdateGame()
{
}

// 출력 생성
void Game::GenerateOutput()
{
}