
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <iostream>
#include "motus-gui.h"

extern "C" int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    GfxEngine mGfx;

    if (mGfx.Initialize())
    {
        std::cout << "[INIT] Success" << std::endl;

        bool loop = true;
        MotusGui motus(mGfx.GetWindowWidth(), mGfx.GetWindowHeight());

        while (loop)
        {
            // 3. On traite les entrées (clavier/souris) et on affiche le jeu
            if (mGfx.StartFrame() == 10000)
            {
                loop = false;
            }
            else
            {
                loop = !motus.Process();
            }
            mGfx.EndFrame();
        }
    }
    else
    {
        std::cout << "[INIT] ERROR" << std::endl;
    }

    std::cout << "[INIT] Galaxie exit" << std::endl;

    return 0;
}
