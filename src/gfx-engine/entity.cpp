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
        if (mClones.size() == 0)
        {
            SDL_Rect r = GetRect();
            r.w *= GetScale().x;
            r.h *= GetScale().y;
            r.x = GetX() + x_offset;
            r.y = GetY() + y_offset;
            Render(renderer, r);
        }
        else
        {
            for (const auto & v : mClones)
            {
                SDL_Rect r = GetRect();
                r.w *= GetScale().x;
                r.h *= GetScale().y;
                r.x = v.x + x_offset;
                r.y = v.y + y_offset;
                Render(renderer, r);
            }
        }

    }
}

void Entity::SetClones(const std::vector<Vector2> &clones)
{
    mClones = clones;
}

void Entity::Render(SDL_Renderer *renderer, const SDL_Rect &pos)
{
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(mTexture, 255, 255, 255);
    SDL_RenderCopyEx(renderer, mTexture, NULL, &pos, GetAngle(), NULL, SDL_FLIP_NONE);
}
