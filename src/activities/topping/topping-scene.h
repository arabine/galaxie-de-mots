#ifndef TOPPING_SCENE_H
#define TOPPING_SCENE_H

#include "gfx-engine.h"
#include "keyboard.h"

class ToppingScene : public Scene, public Keyboard::IKeyEvent
{
public:
    ToppingScene(GfxSystem &s);

    void Initialize();

private:

    std::shared_ptr<Keyboard> mKeyboard;

    // From Keyboard::IKeyEvent
    virtual void KeyPressed(char c) override;
    virtual void EnterPressed() override;
    virtual void BackspacePressed() override;
};


#endif // TOPPING_SCENE_H
