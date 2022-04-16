#include "letter.h"
#include "gfx-engine.h"
#include "common.h"
#include <algorithm>
#include <string>

Letter::Letter(GfxSystem &s, const std::string &fileName, float scale, std::function<void ()> callback)
    : Image(s, fileName, true)
    , mCallback(callback)
    , mScale(scale)
{
    SetSvgScale(scale);
}

void Letter::OnClick()
{
    if (mCallback && mIsActive)
    {
        mCallback();
    }
}

std::string Letter::UpdateSvg(const std::string &svg)
{
    std::string letterSvg = replaceStringAll(svg, "{{BACKGROUND_COLOR}}", mBackgroundColor);
    letterSvg = replaceStringAll(letterSvg, "{{FOREGROUND_COLOR}}", mForegroundColor);
    letterSvg = replaceStringAll(letterSvg, "{{BORDER_WIDTH}}", std::to_string(mBorderWidth));
    letterSvg = replaceStringAll(letterSvg, "{{BORDER_COLOR}}", mBorderColor);
    letterSvg = replaceStringAll(letterSvg, "{{BACKGROUND_OPACITY}}", std::to_string(mBackgroundOpacity));
    letterSvg = replaceStringAll(letterSvg, "{{POINTS_OPACITY}}", std::to_string(mPointsOpacity));
    return letterSvg;
}

void Letter::SetActive(bool active)
{
    mIsActive = active;
}

void Letter::SetLetter(char c)
{
    mChar = c;
}

void Letter::SetCode(char c)
{
    mCode = c;
}

void Letter::SetBackgroundColor(const std::string &color)
{
    mBackgroundColor = color;
}

void Letter::SetForegroundColor(const std::string &color)
{
    mForegroundColor = color;
}

void Letter::SetBorderColor(const std::string &color)
{
    mBorderColor = color;
}

void Letter::SetBorderWidth(uint32_t width)
{
    mBorderWidth = width;
}

void Letter::SetShowPoints(bool show)
{
    mShowPoints = show;
}

void Letter::SetBackgroundOpacity(float opacity)
{
    mBackgroundOpacity = opacity;
}

void Letter::SetPointsOpacity(float opacity)
{
    mPointsOpacity = opacity;
}

