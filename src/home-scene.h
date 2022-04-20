#ifndef HOMESCENE_H
#define HOMESCENE_H

#include "gfx-engine.h"

class HomeScene : public Scene
{
public:
    HomeScene(GfxSystem &s);
    virtual void Draw(SDL_Renderer *renderer) override;
private:

    std::shared_ptr<Image> mTileMotus;
    std::shared_ptr<Image> mTileTopping;


    void DrawWelcomeWindow();
};

#endif // HOMESCENE_H
