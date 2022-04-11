#ifndef LETTER_H
#define LETTER_H

#include "gfx-engine.h"

class Letter : public Entity
{
public:
    Letter(GfxSystem &s, char letter);
    virtual void OnCreate(SDL_Renderer *renderer) override;

    void SetBackgroundColor(SDL_Renderer *renderer, const std::string &backgroundColor, const std::string &foregroundColor, bool showPoints);
private:
    char mLetter;
    std::string mLetterSvg;
};

#endif // LETTER_H
