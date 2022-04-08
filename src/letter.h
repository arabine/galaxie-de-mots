#ifndef LETTER_H
#define LETTER_H

#include "gfx-engine.h"

class Letter : public Entity
{
public:
    Letter(GfxSystem &s, char letter);
    virtual void OnCreate(SDL_Renderer *renderer) override;

    virtual void Draw(SDL_Renderer *renderer) override;

private:
    char mLetter;
    std::string mLetterSvg;
    SDL_Texture *mTexture = nullptr;
};

#endif // LETTER_H
