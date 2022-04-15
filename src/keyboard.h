#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "gfx-engine.h"
#include "letter.h"

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

    void SetUsedLetters(const std::string &word, std::string codage);

private:
    IKeyEvent &mKeyEvent;

    std::list<std::shared_ptr<Letter>> mLetters;
};

#endif // KEYBOARD_H
