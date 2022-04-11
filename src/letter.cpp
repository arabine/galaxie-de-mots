#include "letter.h"
#include "gfx-engine.h"

#include <algorithm>
#include <string>

static std::string replaceStringAll(std::string str, const std::string& old, const std::string& new_s)
{
    if(!old.empty())
    {
        size_t pos = str.find(old);
        while ((pos = str.find(old, pos)) != std::string::npos) {
             str = str.replace(pos, old.length(), new_s);
             pos += new_s.length();
        }
    }
    return str;
}



Letter::Letter(GfxSystem &s, char letter)
    : Entity(s)
    , mLetter(letter)
{

}

/*

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


  */


void Letter::SetBackgroundColor(SDL_Renderer *renderer, const std::string &backgroundColor, const std::string &foregroundColor, bool showPoints)
{
    std::string letterSvg = replaceStringAll(mLetterSvg, "{{BACKGROUND}}", backgroundColor);
    letterSvg = replaceStringAll(letterSvg, "{{LETTER_COLOR}}", foregroundColor);
    letterSvg = replaceStringAll(letterSvg, "{{POINTS_COLOR}}", showPoints ? foregroundColor : backgroundColor);

    SetTexture(Image::RenderSVG(renderer, letterSvg.data(), 0.4));
}

void Letter::OnCreate(SDL_Renderer *renderer)
{
    std::string fileName = "letters/letter_";
    fileName.push_back(mLetter);
    fileName += ".svg";
    if (GfxEngine::LoadFile(fileName.c_str(), mLetterSvg))
    {
        SetBackgroundColor(renderer, "#D3952A", "white", false);
    }
    else
    {
        LOG_ERROR("[LETTER] Cannot load image");
    }
}

