#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "gfx-engine.h"
#include "letter.h"

#include <map>

class Keyboard : public Group
{
public:
    class IKeyEvent
    {
    public:
        ~IKeyEvent() {}

        virtual void KeyPressed(char c) = 0;
        virtual void EnterPressed() = 0;
        virtual void BackspacePressed() = 0;
    };

    Keyboard(GfxSystem &s, IKeyEvent &keyEvent);

    virtual void ProcessEvent(const SDL_Event &event) override;

    void SetUsedLetters(const std::string &word, std::string codage);

    void Initialize();
private:
    IKeyEvent &mKeyEvent;

    std::map<char, char> mCodage;
    std::list<std::shared_ptr<Letter>> mLetters;
};

#endif // KEYBOARD_H
