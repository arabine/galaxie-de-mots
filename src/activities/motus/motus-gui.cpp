#include "motus-gui.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>


MotusGui::MotusGui(GfxSystem &s)
    : Scene(s)
{
    mMotus.Initialize();

    mTextWin = "Youpiii tu as gagné. Une autre partie ?";
    mTextLost = "Hooo mince alors tu as perdu :(\nLe mot était : ";

    mKeyboard = std::make_shared<MotusKeyboard>(GetSystem(), mMotus);

    AddGroup(mKeyboard);
}

