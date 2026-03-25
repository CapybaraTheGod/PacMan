#pragma once
#include "Component.h"
#include <SDL2/SDL_render.h>

class SpriteComponent : public Component
{
public:
	// 생성자
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	// 소멸자
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

private:
	SDL_Texture* mTexture;

	// 화가 알고리즘에서 사용하는 그리기 순서
	int mDrawOrder;
	// 텍스쳐의 너비, 높이
	int mTexWidth;
	int mTexHeight;
};