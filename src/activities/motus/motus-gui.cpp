#include "motus-gui.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>


MotusGui::MotusGui(GfxSystem &s)
    : Scene(s)
    , mMotus(*this)
{
    mKeyboard = std::make_shared<Keyboard>(GetSystem(), *this);
    AddGroup(mKeyboard);

    mGrid = std::make_shared<MotusGrid>(GetSystem(), mMotus);
    AddGroup(mGrid);
}

void MotusGui::Draw(SDL_Renderer *renderer)
{
    Scene::Draw(renderer);

    if (mMessage.size())
    {
        DrawInfoWindow();
    }
}

void MotusGui::Initialize()
{
    mMotus.Initialize();
}

void MotusGui::Message(const std::string &message)
{
    mMessage = message;
}

void MotusGui::AppendLetter(char c)
{
    if (mGrid)
    {
        mGrid->AppendLetter(c);
    }
}

void MotusGui::RemoveLast()
{
    if (mGrid)
    {
        mGrid->DeleteLast();
    }
}

void MotusGui::Validate(const std::string &codage)
{
    if (mGrid)
    {
        mGrid->Validate(codage);
    }

    if (mKeyboard)
    {
        mKeyboard->SetUsedLetters(mMotus.GetLastWord(), codage);
    }
}

void MotusGui::NewGame()
{
    LOG_DEBUG("Word to guess: " + mMotus.GetWordToGuess());
    if (mGrid)
    {
        mGrid->Initialize();
    }

    if (mKeyboard)
    {
        mKeyboard->Initialize();
    }
}


// -----------  LES CALLBACKS CLAVIER sont redirigés vers le moteur de jeu uniquement
void MotusGui::KeyPressed(char c)
{
    mMotus.AppendLetter(c);
}

void MotusGui::EnterPressed()
{
    mMotus.Submit();
}

void MotusGui::BackspacePressed()
{
    mMotus.RemoveLast();
}


void MotusGui::DrawInfoWindow()
{
    static bool started = false;

    // On ne cache pas la fenêtre automatiquement lorsque le jeu est terminé
    if (!mMotus.IsEnd())
    {
        if (!started)
        {
            started = true;
            mTimer.tick();
        }
        else
        {
            mTimer.tock();
            if (mTimer.duration().count() >= 2000) {
                started = false;
                mMessage.clear();
            }
        }
    }

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowBgAlpha(1.0f); // Transparent background
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Always);
    //        ImGui::SetWindowFontScale(2.0);
    ImGui::SetNextWindowSize(ImVec2(400, 100));

    ImGui::GetStyle().FrameBorderSize = 2;
    if (ImGui::Begin("Info", NULL, window_flags))
    {
        ImGui::Text("%s", mMessage.c_str());
        if (mMotus.IsEnd())
        {
            if (!ImGui::IsAnyItemActive())
            {
                ImGui::SetKeyboardFocusHere();
            }

            if (ImGui::Button("Rejouer ?"))
            {
                started = false;
                mMessage.clear();
                mMotus.Initialize();
            }
        }
    }
    ImGui::End();
}
