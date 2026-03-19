#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

// 생성자
Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mPaddleDir(0)
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

	// ball과 paddle 위치 초기화
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -150.0f;
	mBallVel.y = 235.0f;
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

	// 위아래 방향키로 paddle의 위치 업데이트
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_DOWN])
		mPaddleDir += 1;
	if (state[SDL_SCANCODE_UP])
		mPaddleDir -= 1;
}

// 게임 업데이트
void Game::UpdateGame()
{
	// 마지막 프레임 이후로 16ms가 경과할 때 까지 대기
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// deltaTime = 현재 프레임 틱값과 이전 프레임 틱값의 차
	// 차를 초 단위로 변환
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// 최대 델타 시간값으로 고정
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 다음 프레임을 위한 틱값 갱신
	mTicksCount = SDL_GetTicks();

	// 델타 시간 함수로 게임 오브젝트 갱신
	mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
	// paddle이 화면 영역을 벗어나는지 확인
	if (mPaddlePos.y < (paddleH / 2.0f + thickness))
	{
		mPaddlePos.y = paddleH / 2.0f + thickness;
	}
	else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
	{
		mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
	}
	
	// ball의 velocity에 맞게 position 업데이트
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// paddle과 ball의 y좌표 차이 (높이차)
	float diff = mPaddlePos.y - mBallPos.y;
	// 하지만 절대값이 필요함
	diff = (diff > 0.0f) ? diff : -diff;
	
	if (
		diff <= paddleH / 2.0f &&
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.0f;
	}

	// ball의 y 위치에 따라 바닥(천장)에 부딪히는 경우 이동방향 반전
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
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

	// 그리기 색상 보라색 변경
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);

	// 윗쪽 벽 그리기
	SDL_Rect wall{
		0, // 왼쪽 위 x 좌표 
		0, // 왼쪽 위 y 좌표
		1024, // Width
		thickness // Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// 그리기 색상 흰색으로 변경
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// SDL_Rect ball 구조체 초기화
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness/2),
		static_cast<int>(mBallPos.y - thickness/2),
		thickness,
		thickness
	};
	// 공 그리기
	SDL_RenderFillRect(mRenderer, &ball);

	// paddle 그리기
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// 전면 버퍼와 후면 버퍼를 교환
	SDL_RenderPresent(mRenderer);
}