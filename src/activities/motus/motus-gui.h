#ifndef MOTUS_GUI_H
#define MOTUS_GUI_H

#include "motus.h"
#include "gfx-engine.h"
#include "motus-keyboard.h"
#include "motus-grid.h"

class MotusGui : public Scene, public Motus::IEvent
{
public:
    MotusGui(GfxSystem &s);

    void Initialize();

private:
    Motus mMotus;

    // From Motus::IEvent
    virtual void AppendLetter(char c) override;
    virtual void RemoveLast() override;
    virtual void Message(const std::string &message) override;
    virtual void Validate(const std::string &codage) override;
    virtual void InitializeGame() override;

    std::shared_ptr<MotusKeyboard> mKeyboard;
    std::shared_ptr<MotusGrid> mGrid;
};


#endif // MOTUS_GUI_H
