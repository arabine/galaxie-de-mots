
#include "motus-keyboard.h"

#include "letter.h"

//  mMotus.Submit(mMessage);
class Enter : public Entity
{
public:
    Enter(GfxSystem &s, Motus &motus)
        : Entity(s)
        , mMotus(motus)
    {

    }
    virtual void OnCreate(SDL_Renderer *renderer) override
    {
        std::string fileName = "letters/enter.svg";
        if (GfxEngine::LoadFile(fileName.c_str(), mSvg))
        {
            SetTexture(Image::RenderSVG(renderer, mSvg.data(), 0.4));
        }
        else
        {
            LOG_ERROR("[ENTER] Cannot load image");
        }
    }

private:
    Motus &mMotus;
    std::string mSvg;
};

// mMotus.RemoveLast();
class Backspace : public Entity
{
public:
    Backspace(GfxSystem &s, Motus &motus)
        : Entity(s)
        , mMotus(motus)
    {

    }
    virtual void OnCreate(SDL_Renderer *renderer) override
    {
        std::string fileName = "letters/backspace.svg";
        if (GfxEngine::LoadFile(fileName.c_str(), mSvg))
        {
            SetTexture(Image::RenderSVG(renderer, mSvg.data(), 0.4));
        }
        else
        {
            LOG_ERROR("[ENTER] Cannot load image");
        }
    }

private:
    Motus &mMotus;
    std::string mSvg;
};

MotusKeyboard::MotusKeyboard(GfxSystem &s, Motus &motus)
    : Group(s)
    , mMotus(motus)
{
    static const char keyboard[] = { 'a', 'z', 'e', 'r', 't', 'y','u', 'i', 'o', 'p', '\n',
                                     'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '\n',
                                     '?', 'w', 'x', 'c', 'v', 'b', 'n', '<',
                                   };
    int y = 0;
    int x = 0;
    int offset = 50;

    for (int i = 0; i < sizeof(keyboard); i++)
    {
        if (keyboard[i] == '\n')
        {
            // new line
            y += offset;
            x = 0;
        }
        else if (keyboard[i] == '?')
        {
            auto l = std::make_shared<Enter>(GetSystem(), mMotus);
            l->SetVisible(true);
            l->SetPos(x, y);
            AddEntity(l);

            x += 2* offset;

        }
        else if (keyboard[i] == '<')
        {
            auto l = std::make_shared<Backspace>(GetSystem(), mMotus);
            l->SetVisible(true);
            l->SetPos(x, y);
            AddEntity(l);

            x += 2 * offset;
        }
        else
        {
            auto l = std::make_shared<Letter>(GetSystem(), keyboard[i]);
            l->SetVisible(true);
            l->SetPos(x, y);
            AddEntity(l);

            mLetters.push_back(l);

            x += offset;
        }
    }

    SetOrigin(50, 200);
}



