// Component.cpp
#include "Component.h"
#include "Actor.h"

// 부품이 태어날 때
Component::Component(Actor* owner, int updateOrder)
    : mOwner(owner)
    , mUpdateOrder(updateOrder)
{
    // 핵심 포인트!!!
    // "주인님(mOwner)아, 당신의 수첩에 나(this)를 추가해 주세요!"
    mOwner->AddComponent(this);
}

// 부품이 파괴될 때
Component::~Component()
{
    // "주인님(mOwner)아, 당신의 수첩에서 나(this)를 지워 주세요!"
    mOwner->RemoveComponent(this);
}

// 기본 업데이트 함수
void Component::Update(float deltaTime)
{
    // 기본 부품은 스스로 하는 일이 없습니다.
    // 상속받은 자식들(SpriteComponent 등)이 각자 알아서 기능을 채워 넣을 겁니다.
}