
#include "motus-keyboard.h"

#include "letter.h"
#include "button.h"

static const double DEFAULT_SCALE = 0.4;

class Enter : public Button
{
public:
    Enter(GfxSystem &s, Motus &motus)
        : Button(s, "letters/enter.svg")
        , mMotus(motus)
    {

    }

    virtual void OnClick()
    {
        LOG_DEBUG("Enter clicked");
        mMotus.Submit();
    }

private:
    Motus &mMotus;
};


class Backspace : public Button
{
public:
    Backspace(GfxSystem &s, Motus &motus)
        : Button(s, "letters/backspace.svg")
        , mMotus(motus)
    {

    }

    virtual void OnClick()
    {
        LOG_DEBUG("Backspace clicked");
        mMotus.RemoveLast();
    }
private:
    Motus &mMotus;
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

            x += 2 * offset;
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
            char key = keyboard[i];
            auto l = std::make_shared<Letter>(GetSystem(), std::string("letters/letter_") + key + std::string(".svg"), DEFAULT_SCALE, [key, this] {
                LOG_DEBUG(std::string("Letter ") + key + std::string(" CLICKED"));
                mMotus.AppendLetter(key);
            });
            l->SetVisible(true);
            l->SetPos(x, y);
            AddEntity(l);

            mLetters.push_back(l);

            x += offset;
        }
    }

    SetOrigin(50, GetSystem().GetWindowSize().h - 200);
}

