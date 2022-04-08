#ifndef LETTER_TILE_H
#define LETTER_TILE_H

#include "gfx-engine.h"

class LetterTile : public Entity
{
public:
    LetterTile(GfxSystem &s);
    virtual void OnCreate(SDL_Renderer *renderer) override;

    virtual void Draw(SDL_Renderer *renderer) override;

private:
    std::string mLetterTileSvg;
    SDL_Texture *mTexture = nullptr;
};

#endif // LETTER_TILE_H
