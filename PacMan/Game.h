// Game.h
#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Game
{
public:
    Game();
    // 세상을 켜고, 굴리고, 끄는 3대장 함수
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // 🌟 새롭게 추가할 그림 부품 관리 함수!
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

private:
    // RunLoop() 안에서 매 프레임마다 실행될 3단계
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // SDL 창과 그림을 그릴 붓(Renderer)
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    // 🌟 배우들을 관리할 명부와 상태 스위치!
    std::vector<class Actor*> mActors;        // 현재 무대 위 배우들
    std::vector<class Actor*> mPendingActors; // 대기실의 배우들
    bool mUpdatingActors;                     // "지금 무대 업데이트 중?" 스위치

    // 🌟 1. 모든 그림 부품들을 담아둘 '그리기 전용 명단'
    std::vector<class SpriteComponent*> mSprites;

    // 게임이 계속 실행 중인지 체크하는 스위치
    bool mIsRunning;
};