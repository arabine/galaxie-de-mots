#include "letter.h"
#include "gfx-engine.h"
#include "common.h"
#include <algorithm>
#include <string>

/*
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(58, 58, 60, 255)); // gris
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(211, 149, 42, 255)); // orange
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(62, 170, 66, 255)); // vert
*/

Letter::Letter(GfxSystem &s, const std::string &fileName, float scale, std::function<void ()> callback)
    : Button(s, fileName)
    , mCallback(callback)
    , mScale(scale)
{

}


void Letter::SetBackgroundColor(SDL_Renderer *renderer, const std::string &backgroundColor, const std::string &foregroundColor, bool showPoints)
{
    std::string letterSvg = replaceStringAll(mLetterSvg, "{{BACKGROUND}}", backgroundColor);
    letterSvg = replaceStringAll(letterSvg, "{{LETTER_COLOR}}", foregroundColor);
    letterSvg = replaceStringAll(letterSvg, "{{POINTS_COLOR}}", showPoints ? foregroundColor : backgroundColor);

    SetTexture(Image::RenderSVG(renderer, letterSvg.data(), mScale));
}

void Letter::OnCreate(SDL_Renderer *renderer)
{
    if (GfxEngine::LoadFile(FileName().data(), mLetterSvg))
    {
        SetBackgroundColor(renderer, "#D3952A", "white", false);
    }
    else
    {
        LOG_ERROR("[LETTER] Cannot load image");
    }
}

void Letter::OnClick()
{
    if (mCallback)
    {
        mCallback();
    }
}

void Letter::SetActive(bool active)
{
    mIsActive = active;
}

