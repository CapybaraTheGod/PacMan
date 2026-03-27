// Actor.h
#pragma once
#include <vector>
#include "Math.h"

class Actor {
public:
    // 상태 정의 (활성, 일시정지, 파괴 등)
    enum State { EActive, EPaused, EDead };

    Actor(class Game* game);
    virtual ~Actor();

    // Game에서 호출할 업데이트 함수
    void Update(float deltaTime);
    // 컴포넌트들을 업데이트
    void UpdateComponents(float deltaTime);
    // 액터만의 고유한 로직 (상속받아 구현)
    virtual void UpdateActor(float deltaTime);

    // Getters / Setters
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    class Game* GetGame() { return mGame; }

    // 컴포넌트 추가/제거
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

private:
    State mState;

    // 변환 정보 (위치, 크기, 회전)
    Vector2 mPosition;
    float mScale;
    float mRotation;

    // 이 액터가 소유한 컴포넌트들
    std::vector<class Component*> mComponents;
    class Game* mGame;
};