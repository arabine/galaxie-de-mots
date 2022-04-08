#include "letter-tile.h"
#include "gfx-engine.h"

/*

#include <iostream>
#include <algorithm>
#include <string>

int main()
{
    std::string s = "C**";
    const char x = '*';
    const char y = '+';

    std::replace(s.begin(), s.end(), x, y);
    std::cout << s;

    return 0;
}


*/

LetterTile::LetterTile(GfxSystem &s)
    : Entity(s)
{

}

void LetterTile::OnCreate(SDL_Renderer *renderer)
{
    if (GfxEngine::LoadFile("letters/background.svg", mLetterTileSvg))
    {
       // std::string newCarColor = replaceStringAll(mDeuxCvSVG, "{{COLOR}}", "#a17321");

        mTexture = Image::RenderSVG(renderer, mLetterTileSvg.data());
        int w = 0;
        int h = 0;
        // get the width and height of the texture
        if (SDL_QueryTexture(mTexture, NULL, NULL, &w, &h) == 0)
        {
            SetSize(w, h);
        }
    }
    else
    {
        LOG_ERROR("[LETTER] Cannot load image");
    }
}

void LetterTile::Draw(SDL_Renderer *renderer)
{
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureColorMod(mTexture, 255, 255, 255);
    SDL_RenderCopyEx(renderer, mTexture, NULL, &GetRect(), GetAngle(), NULL, SDL_FLIP_NONE);
} 
