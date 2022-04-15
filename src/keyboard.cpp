
#include "keyboard.h"
#include "letter.h"

static const double DEFAULT_SCALE = 0.4;

class Enter : public Image
{
public:
    Enter(GfxSystem &s, Keyboard::IKeyEvent &keyEvent)
        : Image(s, "letters/enter.svg", true)
        , mKeyEvent(keyEvent)
    {
        SetSvgScale(DEFAULT_SCALE);
    }

    virtual void OnClick()
    {
//        LOG_DEBUG("Enter clicked");
        mKeyEvent.EnterPressed();
    }

private:
    Keyboard::IKeyEvent &mKeyEvent;
};

class Backspace : public Image
{
public:
    Backspace(GfxSystem &s, Keyboard::IKeyEvent &keyEvent)
        : Image(s, "letters/backspace.svg", true)
        , mKeyEvent(keyEvent)
    {
        SetSvgScale(DEFAULT_SCALE);
    }

    virtual void OnClick()
    {
//        LOG_DEBUG("Backspace clicked");
        mKeyEvent.BackspacePressed();
    }
private:
    Keyboard::IKeyEvent &mKeyEvent;
};


Keyboard::Keyboard(GfxSystem &s, IKeyEvent &keyEvent)
    : Group(s)
    , mKeyEvent(keyEvent)
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
            auto l = std::make_shared<Enter>(GetSystem(), mKeyEvent);
            l->SetVisible(true);
            l->SetPos(x, y);
            AddEntity(l);

            x += 2 * offset;
        }
        else if (keyboard[i] == '<')
        {
            auto l = std::make_shared<Backspace>(GetSystem(), mKeyEvent);
            l->SetVisible(true);
            l->SetPos(x, y);
            AddEntity(l);

            x += 2 * offset;
        }
        else
        {
            char key = keyboard[i];
            auto l = std::make_shared<Letter>(GetSystem(), std::string("letters/letter_") + key + std::string(".svg"), DEFAULT_SCALE, [key, this] {
           //     LOG_DEBUG(std::string("Letter ") + key + std::string(" CLICKED"));
                mKeyEvent.KeyPressed(key);
            });
            l->SetVisible(true);
            l->SetActive(true);
            l->SetPos(x, y);
            AddEntity(l);

            mLetters.push_back(l);

            x += offset;
        }
    }

    SetOrigin(50, GetSystem().GetWindowSize().h - 200);
}

