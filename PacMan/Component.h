// Component.h
#pragma once

class Component
{
public:
    // 생성자: 부품이 태어날 때, '나의 주인님(Actor)'과 '업데이트 순위'를 받습니다.
    // updateOrder의 기본값은 100으로 설정해 둡니다.
    Component(class Actor* owner, int updateOrder = 100);

    // 소멸자: 부품이 파괴될 때 불립니다.
    virtual ~Component();

    // 매 프레임마다 불릴 업데이트 함수 (자식들이 덮어쓸 수 있게 virtual)
    virtual void Update(float deltaTime);

    // 내 업데이트 순위가 몇 번인지 알려주는 함수
    int GetUpdateOrder() const { return mUpdateOrder; }

protected:
    // '나를 소유하고 있는 주인님'의 주소 (아주 중요!)
    class Actor* mOwner;

    // 내 업데이트 순위 (숫자가 낮을수록 먼저 실행됨)
    int mUpdateOrder;
};