#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"


Game::Game()
    :mWindow(nullptr)
    , mRenderer(nullptr)
    , mUpdatingActors(false)
    , mIsRunning(true)
{
}

bool Game::Initialize() {
    // 1. SDL 시스템 전체 초기화 (비디오 기능 위주)
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL 초기화 실패: %s", SDL_GetError());
        return false;
    }

    // 2. 윈도우 생성 (제목, X, Y, 너비, 높이, 플래그)
    mWindow = SDL_CreateWindow("Game Programming in C++ (Ch2)", 100, 100, 1024, 768, 0);
    if (!mWindow) {
        return false;
    }

    // 3. 렌더러 생성 (윈도우, 드라이버 인덱스, 옵션 플래그)
    // SDL_RENDERER_ACCELERATED: 그래픽 카드 사용
    // SDL_RENDERER_PRESENTVSYNC: 수직 동기화 (프레임 안정화)
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        return false;
    }

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

// 🌟 배우 등록 (대기실 vs 본 무대)
void Game::AddActor(class Actor* actor)
{
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor); // 업데이트 중이면 일단 대기실로!
    }
    else {
        mActors.emplace_back(actor);        // 아니면 바로 본 무대로!
    }
}
// 🌟 배우 삭제 (어디 있든 찾아서 지운다)
void Game::RemoveActor(class Actor* actor)
{
    // 1. 대기실에 있나?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        mPendingActors.erase(iter);
    }

    // 2. 본 무대에 있나?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        mActors.erase(iter);
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            mIsRunning = false;
        }
    }
}

// 🌟 1. 그림 명단에 추가하기 (줄 세우기 알고리즘)
void Game::AddSprite(SpriteComponent* sprite)
{
    // 내가 가진 번호표(mDrawOrder)를 확인합니다.
    int myDrawOrder = sprite->GetDrawOrder();

    // 명단의 처음부터 끝까지 훑어보면서 내가 들어갈 자리를 찾습니다!
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        // 만약 나보다 번호표 숫자가 '높은' 애를 발견했다면?
        // "아! 내 자리는 저 녀석 바로 앞이구나!" 하고 멈춥니다(break).
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    // 찾은 그 위치(iter)에 나를 쏙 집어넣습니다!
    mSprites.insert(iter, sprite);
}

// 🌟 2. 그림 명단에서 삭제하기
void Game::RemoveSprite(SpriteComponent* sprite)
{
    // 명단에서 나(sprite)를 찾아서 지워버립니다.
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if (iter != mSprites.end())
    {
        mSprites.erase(iter);
    }
}

// 🌟 게임 루프의 핵심 심장부! (여기가 진짜 중요합니다)
void Game::UpdateGame() {
    // (이 윗부분에는 프레임 속도 조절(Delta Time) 코드가 들어갑니다)

    // 1. "지금부터 모든 배우들 업데이트 시작한다!" 스위치 ON
    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->Update(0.016f); // (임시 델타 타임) 
    }
    // 2. "업데이트 끝!" 스위치 OFF
    mUpdatingActors = false;

    // 3. 업데이트가 끝났으니, 대기실에 있던 신인 배우들을 전부 본 무대로 부른다!
    for (auto pending : mPendingActors) {
        mActors.push_back(pending);
    }
    mPendingActors.clear(); // 대기실 비우기!

    // 4. 죽은(EDead) 배우들 찾아내서 메모리에서 영구 삭제(delete)
    std::vector<Actor*> deadActors;
    for (auto actor : mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.push_back(actor);
        }
    }

    // delete를 호출하면 Actor의 소멸자(~Actor)가 불리고, 
    // 거기서 알아서 RemoveActor를 호출해서 배열에서도 빠지게 됩니다.
    for (auto actor : deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    // 1. 그리기 색상 설정 (R, G, B, A) -> 파란색
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

    // 2. 백 버퍼를 현재 색상으로 지우기
    SDL_RenderClear(mRenderer);

    // 3. 그림 명단(mSprites)에 있는 모든 부품들을 순서대로 그린다!
    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }

    // 4. 백 버퍼와 프론트 버퍼 교체 (화면 표시)
    SDL_RenderPresent(mRenderer);
}