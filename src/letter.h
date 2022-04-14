#ifndef LETTER_H
#define LETTER_H

#include "gfx-engine.h"
#include "image.h"

class Letter : public Image
{
public:
    Letter(GfxSystem &s, const std::string &fileName, float scale, std::function<void(void)> callback);

    virtual void OnClick() override;
    virtual std::string UpdateSvg(const std::string &svg) override;

    void SetActive(bool active);
    void SetEmpty();

    void SetBackgroundColor(const std::string &color);
    void SetForegroundColor(const std::string &color);
    void SetBorderColor(const std::string &color);
    void SetBorderWidth(uint32_t width);
    void SetShowPoints(bool show);
    void SetBackgroundOpacity(float opacity);
    void SetPointsOpacity(float opacity);

private:
    std::function<void(void)> mCallback;
    bool mIsActive = false;
    float mScale;
    std::string mLetterSvg;

    // Style
    std::string mBackgroundColor{"#585860"};
    std::string mForegroundColor{"white"};
    bool mShowPoints{false};
    float mBackgroundOpacity{1.0};
    float mPointsOpacity{0.0};
    uint32_t mBorderWidth{0};
    std::string mBorderColor{"white"};

};

#endif // LETTER_H
