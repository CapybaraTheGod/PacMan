#pragma once
// SpriteComponent.h
#pragma once
#include "Component.h"
#include <SDL2/SDL.h>

// Component를 상속받습니다! (나는 부품의 일종이다)
class SpriteComponent : public Component
{
public:
    // 생성자: drawOrder가 낮을수록 배경에 가깝게(먼저) 그려집니다.
    // (기본 부품의 updateOrder와 비슷한 개념입니다)
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    // 매 프레임마다 화면에 내 이미지를 그리는 함수
    virtual void Draw(SDL_Renderer* renderer);

    // 이 부품에 텍스처(이미지)를 장착하는 함수
    virtual void SetTexture(SDL_Texture* texture);

    // 정보 가져오기 (Getters)
    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }

protected:
    SDL_Texture* mTexture; // 내가 화면에 그릴 이미지 데이터
    int mDrawOrder;        // 그리기 순서 (배경=10, 플레이어=100 등)
    int mTexWidth;         // 이미지의 원본 가로 길이
    int mTexHeight;        // 이미지의 원본 세로 길이
};