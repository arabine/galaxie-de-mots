#ifndef MOTUS_KEYBOARD_H
#define MOTUS_KEYBOARD_H

#include "gfx-engine.h"
#include "motus.h"
#include "letter.h"

class MotusKeyboard : public Group
{
public:
    MotusKeyboard(GfxSystem &s, Motus &motus);

private:
    Motus &mMotus;
    std::string mMessage;

    std::list<std::shared_ptr<Letter>> mLetters;
};

#endif // MOTUS_KEYBOARD_H
