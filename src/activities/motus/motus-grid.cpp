 
#include "motus-grid.h"
/*
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
      //      mMessage.clear();
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
          //  ImGui::Text("%s", mMessage.c_str());
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
*/

static const double TILE_SIZE = 0.8;

MotusGrid::MotusGrid(GfxSystem &s, Motus &motus)
    : Group(s)
    , mMotus(motus)
{
    SetOrigin(50, 100);

    mEmptyTile = std::make_shared<Letter>(GetSystem(), "letters/empty_tile.svg", TILE_SIZE, [] {});
    mEmptyTile->SetActive(false);
    mEmptyTile->SetVisible(true);
    AddEntity(mEmptyTile);

    mLetterPos = 0;

    int x = 0;
    int y = 0;
    for (int i = 0; i < mMotus.GetNbLines(); i++)
    {
        for (int j = 0; j < mMotus.GetNbLetters(); j++)
        {
            mClones.push_back(Vector2(x, y, true));
            x += 90;
        }
        y += 90;
        x = 0;
    }
    mEmptyTile->SetClones(mClones);
}

void MotusGrid::DeleteLast()
{
    if (mLetterPos > 0)
    {
        mLetterPos--;
        mClones[mLetterPos].enable = true;
        mEmptyTile->SetClones(mClones);
        uint32_t idToDelete = mGrid.back()->GetId();
        mGrid.pop_back();
        DeleteEntity(idToDelete);
    }
}

void MotusGrid::AppendLetter(char c)
{
    if (mLetterPos < mClones.size())
    {
        // Disable empty tile
        mClones[mLetterPos].enable = false;
        mEmptyTile->SetClones(mClones);

        // On va maintenant créer une tile de lettre
        auto t = std::make_shared<Letter>(GetSystem(), std::string("letters/letter_") + c + std::string(".svg"), TILE_SIZE, [] {});
        t->SetActive(false);
        t->SetVisible(true);
        t->SetPos(mClones[mLetterPos].x, mClones[mLetterPos].y); // on place la tile à la même place que la tile vide
        AddEntity(t);
        mGrid.push_back(t);

        mLetterPos++;
    }
}

void MotusGrid::ShowMessage(const std::string &message)
{

}

void MotusGrid::Draw(SDL_Renderer *renderer)
{
    Group::Draw(renderer);

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
                      // La lettre n'est pas dans le mot
//                    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(58, 58, 60, 255)); // gris
                }
                else if (codage[j] == '1')
                {
                      // Mauvaise place
//                    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(211, 149, 42, 255)); // orange
                }
                else
                {
                      // Bonne et bien placée
//                    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(62, 170, 66, 255)); // vert
                }
            }
            else
            {
                // Case vide
//                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 255));
            }


        }
//        ImGui::NewLine();
    }

}

