#ifndef HOMESCENE_H
#define HOMESCENE_H

#include "gfx-engine.h"

class HomeScene : public Scene
{
public:
    HomeScene(GfxSystem &s);
    virtual ~HomeScene() {}

    virtual void Draw(SDL_Renderer *renderer) override;

    virtual void Update(double deltaTime) override;

    virtual void OnMessage(MessageQueue &message) override;

private:
    std::string m_debugTxt;

    std::shared_ptr<Image> mTileMotus;
    std::shared_ptr<Image> mTileTopping;

    float mWelcomeSize{0.0};

    void DrawWelcomeWindow();
};

#endif // HOMESCENE_H
