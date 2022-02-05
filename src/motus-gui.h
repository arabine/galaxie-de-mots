#ifndef MOTUSGUI_H
#define MOTUSGUI_H

#include "motus.h"
#include "imgui.h"

class MotusGui
{
public:
    MotusGui(uint32_t w, uint32_t h);

    bool Process();

private:
    Motus mMotus;

    uint32_t mWidth;
    uint32_t mHeight;

    bool DrawMenuBar();
    void DrawWords();
    void DrawKeyboard();

};


#endif // MOTUSGUI_H
