#include "motus-gui.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>


MotusGui::MotusGui(uint32_t w, uint32_t h)
    : mWidth(w)
    , mHeight(h)
{
    mMotus.Initialize();

    mTextWin = "Youpiii tu as gagné. Une autre partie ?";
    mTextLost = "Hooo mince alors tu as perdu :(\nLe mot était : ";
}

bool MotusGui::Process()
{
    bool quit = DrawMenuBar();
    DrawWords();
    DrawKeyboard();

    if (mMessage.size() || mMotus.IsEnd())
    {
        DrawInfoWindow();
    }

    return quit;
}

bool MotusGui::DrawMenuBar()
{
    bool quit = false;
    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if(ImGui::MenuItem("Quit"))
            {
                quit = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    return quit;
}

void MotusGui::DrawInfoWindow()
{
    static bool started = false;

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

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
    ImGui::SetNextWindowPos(ImVec2((mWidth - 400) / 2, 50), ImGuiCond_Always);
    //        ImGui::SetWindowFontScale(2.0);
    ImGui::SetNextWindowSize(ImVec2(400, 80));

    ImGui::GetStyle().FrameBorderSize = 2;
    if (ImGui::Begin("Info", NULL, window_flags))
    {

        if (mMotus.IsEnd())
        {

            if (mMotus.IsWin())
            {
                ImGui::Text("%s", mTextWin.c_str());
            }
            else
            {
                ImGui::Text("%s%s", mTextLost.c_str(), mMotus.GetWord().c_str());
            }

            if (ImGui::Button("Rejouer ?"))
            {
                mMotus.Initialize();
            }
        }
        else
        {
            ImGui::Text("%s", mMessage.c_str());
        }
    }
    ImGui::End();
}

void MotusGui::DrawWords()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
    ImGui::SetNextWindowPos(ImVec2((mWidth - 340) / 2, 140), ImGuiCond_Always);
    //        ImGui::SetWindowFontScale(2.0);
    ImGui::SetNextWindowSize(ImVec2(340, 400));

    ImGui::GetStyle().FrameBorderSize = 2;
    if (ImGui::Begin("Words", NULL, window_flags))
    {
        ImGui::BeginDisabled();
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0); // sinon le texte est gris
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32_WHITE);

        GfxEngine::PushBigFont();

        for (uint32_t i = 0; i < mMotus.GetNbLines(); i++)
        {
            std::string word = mMotus.GetTry(i);
            std::string codage = mMotus.TestWord(word);
            bool validated = mMotus.IsTryValidated(i);

            for (uint32_t j = 0; j < mMotus.GetNbLetters(); j++)
            {
                std::string letter = " ";
                letter[0] = word[j];

                if (validated && (word.size() > j) && (codage.size() > j))
                {
                      if (codage[j] == '0')
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(58, 58, 60, 255)); // gris
                    }
                    else if (codage[j] == '1')
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(211, 149, 42, 255)); // orange
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(62, 170, 66, 255)); // vert
                    }
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 255));
                }

                if (ImGui::Button(letter.c_str(), ImVec2(60, 60)))
                {

                }
                ImGui::PopStyleColor();
                ImGui::SameLine(0.0f, 5.0);
            }
            ImGui::NewLine();
        }

        GfxEngine::PopBigFont();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::EndDisabled();
    }


    ImGui::End();
}

void MotusGui::DrawKeyboard()
{
    static const char keyboard[] = { 'A', 'Z', 'E', 'R', 'T', 'Y','U', 'I', 'O', 'P', '\n',
                                     'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '\n',
                                     '?', 'W', 'X', 'C', 'V', 'B', 'N', '<',
                                   };

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoMove;

    //        ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background
    ImGui::SetNextWindowPos(ImVec2((mWidth - 460) / 2, 600), ImGuiCond_Always);

    int offset = mHeight - 600;

    ImGui::SetNextWindowSize(ImVec2(460, offset));

    ImGui::GetStyle().FrameBorderSize = 0;

    if (ImGui::Begin("Keyboard", NULL, window_flags))
    {
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(99, 99, 99, 255));
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32_WHITE);

        for (int i = 0; i < sizeof(keyboard); i++)
        {
            std::string text;
            text.push_back(keyboard[i]);
            text.push_back(0);
            if (keyboard[i] == '\n')
            {
                ImGui::NewLine();
            }
            else if (keyboard[i] == '?')
            {
                ImGui::SetNextItemWidth(200);
                if (ImGui::Button(ICON_FA_CHECK_CIRCLE, ImVec2(85, 40)))
                {
                    mMotus.Submit(mMessage);
                }
                ImGui::SameLine(0.0f, 5.0);
            }
            else if (keyboard[i] == '<')
            {
                if (ImGui::Button(ICON_FA_BACKSPACE, ImVec2(85, 40)))
                {
                    mMotus.RemoveLast();
                }
                ImGui::SameLine(0.0f, 5.0);
            }
            else
            {
                if (ImGui::Button(text.c_str(), ImVec2(40, 40)))
                {
                    mMotus.AppendLetter(text.at(0));
                }
                ImGui::SameLine(0.0f, 5.0);
            }
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }
    ImGui::End();
}
