#ifndef LETTER_H
#define LETTER_H

#include "gfx-engine.h"
#include "button.h"

class Letter : public Button
{
public:
    Letter(GfxSystem &s, const std::string &fileName, float scale, std::function<void(void)> callback);
    virtual void OnCreate(SDL_Renderer *renderer) override;

    virtual void OnClick() override;

    void SetActive(bool active);
    void SetEmpty();
    void SetBackgroundColor(SDL_Renderer *renderer, const std::string &backgroundColor, const std::string &foregroundColor, bool showPoints);
private:
    std::function<void(void)> mCallback;
    bool mIsActive = false;
    float mScale;
    std::string mLetterSvg;
};

#endif // LETTER_H
