#pragma once
#include <SDL2/SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();

	// 게임 초기화
	bool Initialize();

	// 게임이 끝나기 전까지 게임 루프를 실행
	void RunLoop();

	// 게임 종료
	void Shutdown();
private:
	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// SDL이 생성한 윈도우
	SDL_Window* window;
	// 2D 그리기를 위한 Renderer
	SDL_Renderer* renderer;
	// 게임 시작 이후로 틱의 수
	Uint32 mTicksCount{};
	// 게임이 계속 실행되어야 하는지 판단
	bool IsRunning{true};

	// paddle 들의 위치
	int mPaddleDir;
	int nPaddleDir;
	// 패들 위치
	Vector2 mPaddlePos;
	Vector2 nPaddlePos;

	// 공의 위치
	Vector2 ballPos;
	// 공의 속도
	Vector2 ballVel;
};