#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class Actor;
class SpriteComponent;
class Ship;

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

  void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

  void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
private:
	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loaded (중복 로드 방지를 위한 텍스쳐 관리)
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// 게임 내 모든 객체의 업데이트 관리
	// 게임 내 Actors
  std::vector<Actor*> mActors;
	// 대기 중인 Actors
   std::vector<Actor*> mPendingActors;

	// 그려진 모든 sprite components (화면에 출력될 컴포넌트들만 따로 관리)
   std::vector<SpriteComponent*> mSprites;

	// SDL이 생성한 윈도우
	SDL_Window* mWindow;
	// 2D 그리기를 위한 Renderer
	SDL_Renderer* mRenderer;
	// 틱 계산 
	Uint32 mTicksCount;
	// 게임이 계속 실행되어야 하는지 판단
	bool mIsRunning{true};
	// 액터를 갱신 중인지 판단
	bool mUpdatingActors;

	// Game-specific
   Ship* mShip; // 플레이어의 배
};