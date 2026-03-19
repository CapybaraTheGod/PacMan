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
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("SDL을 초기화 할 수 없었습니다.: %s", SDL_GetError());
		return false;
	}

	// SDL 윈도우 생성하기
	mWindow = SDL_CreateWindow(
		"Game Programming in c++ (Chapter 1)", // 윈도우 제목
		100, // 윈도우의 좌측 상단 x좌표
		100, // 윈도우의 좌측상단 y좌표
		1024, // 윈도우 너비
		768, // 윈도우 높이
		0 // 플래그 (아무런 플래그도 지정하지 않음을 의미)
	);

	if (!mWindow)
	{
		SDL_Log("윈도우 생성 실패: %s", SDL_GetError());
		return false;
	}

	// 창을 생성한 후, SDL Renderer를 생성
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// Render 실패 시
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
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
	// 파란색 지정
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);
	// 후면 버퍼 지우기
	SDL_RenderClear(mRenderer);
	// 전면 버퍼와 후면 버퍼를 교환
	SDL_RenderPresent(mRenderer);
}