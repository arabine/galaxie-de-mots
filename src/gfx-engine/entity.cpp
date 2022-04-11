#include "entity.h"

Entity::Entity(GfxSystem &s)
    : mSystem(s)
{
    mRect.x = 0;
    mRect.y = 0;
    mRect.w = 0;
    mRect.h = 0;
}

Entity::~Entity()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}

void Entity::Draw(SDL_Renderer *renderer, int x_offset, int y_offset)
{
    if (IsVisible() && (mTexture != nullptr))
    {
        SDL_Rect r = GetRect();
        r.w *= GetScale().x;
        r.h *= GetScale().y;
        r.x = GetX() + x_offset;
        r.y = GetY() + y_offset;
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(mTexture, 255, 255, 255);
        SDL_RenderCopyEx(renderer, mTexture, NULL, &r, GetAngle(), NULL, SDL_FLIP_NONE);
    }
}
