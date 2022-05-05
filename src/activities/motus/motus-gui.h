#ifndef MOTUS_GUI_H
#define MOTUS_GUI_H

#include "motus.h"
#include "gfx-engine.h"
#include "keyboard.h"
#include "motus-grid.h"
#include "i_application.h"

class MotusGui : public Scene, public Motus::IGameEvent, public Keyboard::IKeyEvent
{
public:
    MotusGui(GfxSystem &s, IApplication &app);

    void Initialize();

    virtual void Draw(SDL_Renderer *renderer) override;
    virtual void OnCreate(SDL_Renderer *renderer) override;

private:
    Motus mMotus;
    std::shared_ptr<Keyboard> mKeyboard;
    std::shared_ptr<MotusGrid> mGrid;

    std::string mMessage;

    Timer<std::chrono::milliseconds, std::chrono::steady_clock> mTimer;

    // From Motus::IEvent
    virtual void AppendLetter(char c) override;
    virtual void RemoveLast() override;
    virtual void Message(const std::string &message) override;
    virtual void Validate(const std::string &codage) override;
    virtual void NewGame() override;

    // From Keyboard::IKeyEvent
    virtual void KeyPressed(char c) override;
    virtual void EnterPressed() override;
    virtual void BackspacePressed() override;

    // -------------------  PRIVATE
    void DrawInfoWindow();

};


#endif // MOTUS_GUI_H
