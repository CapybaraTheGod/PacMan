// SpriteComponent.cpp
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner) // 부모(Component)의 생성자 먼저 호출!
    , mTexture(nullptr)
    , mDrawOrder(drawOrder)
    , mTexWidth(0)
    , mTexHeight(0)
{
    // 핵심! "감독님, 저 태어났어요! 그리기 명단에 올려주세요!"
    // (주인님을 통해 감독님에게 연락합니다)
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    // "감독님, 저 파괴됩니다. 그리기 명단에서 지워주세요!"
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        // 1. 내가 그려질 사각형(위치와 크기)을 계산합니다.
        SDL_Rect r;

        // 주인님(Actor)의 크기(Scale)를 곱해서 실제 너비/높이를 구함
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

        // 중심점을 기준으로 그리기 때문에, 내 너비/높이의 절반을 빼줍니다.
        r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

        // 2. 화면에 그립니다! (SDL_RenderCopyEx는 회전까지 지원하는 고급 함수입니다)
        // 주의: SDL은 시계 방향이 + 각도인데, 우리 수학은 반시계가 + 라서 마이너스(-)를 붙여줍니다.
        SDL_RenderCopyEx(renderer, mTexture, nullptr, &r,
            -mOwner->GetRotation(),
            nullptr, SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    // 텍스처를 장착할 때, SDL 함수를 이용해 이미지의 원본 가로/세로 픽셀 길이를 알아내서 저장해 둡니다.
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}