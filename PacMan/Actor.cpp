#include "Actor.h"
#include "Component.h"
#include "Game.h"


// 생성자: 액터가 태어날 때
Actor::Actor(Game* game)
    : mState(EActive)
    , mPosition(Vector2::Zero)
    , mScale(1.0f)
    , mRotation(0.0f)
    , mGame(game)
{
    // "감독님! 저 태어났어요! 명단에 올려주세요!"
    mGame->AddActor(this);
}

// 소멸자: 액터가 죽을 때
Actor::~Actor()
{
    // "감독님! 저 이제 갑니다. 명단에서 지워주세요!"
    mGame->RemoveActor(this);

    // 내가 쥐고 있던 부품(컴포넌트)들도 메모리에서 전부 파괴!
    // (메모리 누수를 막기 위한 아주 중요한 작업입니다)
    while (!mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    // 내 상태가 '활성화(EActive)'일 때만 로직을 실행한다.
    if (mState == EActive)
    {
        UpdateComponents(deltaTime); // 1. 부품들 먼저 업데이트
        UpdateActor(deltaTime);      // 2. 내 고유 로직 업데이트
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    // 내 수첩(mComponents)에 있는 모든 부품을 순회하며 작동시킴!
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
    // 여기는 비워둡니다. (virtual 함수)
    // 상속받은 자식(Ship 등)이 자신만의 움직임을 여기에 덮어쓸 겁니다.
}

void Actor::AddComponent(Component* component)
{
    // 1. 추가하려는 부품의 순위(숫자)를 확인합니다.
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();

    // 2. 수첩(벡터)을 처음부터 끝까지 훑어봅니다.
    for (; iter != mComponents.end(); ++iter)
    {
        // 나보다 순위가 낮은(숫자가 큰) 녀석을 발견하면?
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break; // 찾았다! 내 자리는 바로 이 녀석 앞이야! 하고 반복문을 멈춥니다.
        }
    }

    // 3. 찾은 위치(iter)에 부품을 쏙 끼워 넣습니다. 
    // (만약 내가 숫자가 제일 크다면 자연스럽게 맨 뒤에 들어갑니다)
    mComponents.insert(iter, component);
}


void Actor::RemoveComponent(Component* component)
{
    // 1. 수첩의 처음(begin)부터 끝(end)까지 뒤져서, 이 부품과 똑같은 주소를 찾습니다.
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);

    // 2. 만약 끝까지 찾았는데 못 찾은 게 아니라면? (즉, 수첩에서 발견했다면!)
    if (iter != mComponents.end())
    {
        // 3. 수첩에서 그 항목을 싹 지워버립니다.
        mComponents.erase(iter);
    }
}