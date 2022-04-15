#include "motus-gui.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>


MotusGui::MotusGui(GfxSystem &s)
    : Scene(s)
    , mMotus(*this)
{
    mKeyboard = std::make_shared<MotusKeyboard>(GetSystem(), mMotus);
    AddGroup(mKeyboard);

    mGrid = std::make_shared<MotusGrid>(GetSystem(), mMotus);
    AddGroup(mGrid);
}

void MotusGui::Initialize()
{
    mMotus.Initialize();
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

void MotusGui::InitializeGame()
{
    LOG_DEBUG("Word to guess: " + mMotus.GetWord());
    mGrid->Initialize();
}

