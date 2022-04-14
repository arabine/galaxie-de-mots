#include "motus-gui.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>


MotusGui::MotusGui(GfxSystem &s)
    : Scene(s)
    , mMotus(*this)
{
    mMotus.Initialize();

    LOG_DEBUG("Word to guess: " + mMotus.GetWord());

    mTextWin = "Youpiii tu as gagné. Une autre partie ?";
    mTextLost = "Hooo mince alors tu as perdu :(\nLe mot était : ";

    mKeyboard = std::make_shared<MotusKeyboard>(GetSystem(), mMotus);
    AddGroup(mKeyboard);

    mGrid = std::make_shared<MotusGrid>(GetSystem(), mMotus);
    AddGroup(mGrid);
}

void MotusGui::AppendLetter(char c)
{
    mGrid->AppendLetter(c);
}

void MotusGui::RemoveLast()
{
    mGrid->DeleteLast();
}

void MotusGui::Message(const std::string &message)
{
    mGrid->ShowMessage(message);
}

void MotusGui::Validate(const std::string &codage)
{
    mGrid->Validate(codage);
}

