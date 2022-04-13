#ifndef BUTTON_H
#define BUTTON_H

#include "gfx-engine.h"

class Button : public Entity
{
public:
    Button(GfxSystem &s, const std::string &fileName)
        : Entity(s)
        , mFileName(fileName)
    {

    }

    virtual void OnClick() {}

    bool HasClicked(const SDL_Point &pos, const Vector2 &origin) const
    {
        SDL_Rect rect = GetRect();
        rect.x += origin.x;
        rect.y += origin.y;
        return SDL_PointInRect(&pos, &rect);
    }

    virtual void ProcessEvent(const SDL_Event &event, const Vector2 &origin) override
    {
        SDL_Point mousePos;

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            mousePos.x = event.button.x;
            mousePos.y = event.button.y;

           if (HasClicked(mousePos, origin))
           {
               OnClick();
           }
        }
    }

    std::string_view FileName() const
    {
        return std::string_view(mFileName);
    }

    virtual void OnCreate(SDL_Renderer *renderer) override
    {
        if (GfxEngine::LoadFile(mFileName.c_str(), mSvg))
        {
            SetTexture(Image::RenderSVG(renderer, mSvg.data(), 0.4));
        }
        else
        {
            LOG_ERROR("[ENTER] Cannot load image");
        }
    }

private:
    std::string mFileName;
    std::string mSvg;
};


#endif // BUTTON_H
