
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <iostream>
#include "motus-gui.h"

enum Scenes {
    SCENE_NOTHING = 0,
    SCENE_TITLE,
    SCENE_MOTUS,
    SCENE_EXIT = 10000
};

extern "C" int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    GfxEngine mGfx;
    GfxEngine::Message msg;

    if (mGfx.Initialize("Galaxie de mots"))
    {
        std::cout << "[INIT] Success" << std::endl;

        bool loop = true;
        MotusGui motus(mGfx);

        mGfx.AddScene(std::make_shared<MotusGui>(mGfx), SCENE_MOTUS);
        mGfx.SwitchSceneTo(SCENE_MOTUS); // First scene
        mGfx.Warmup();

        while (loop)
        {
            // On traite les entrées (clavier/souris) et on affiche le jeu
            msg.clear();
            if (mGfx.Process(msg) == SCENE_EXIT)
            {
                loop = false;
            }
        }
    }
    else
    {
        std::cout << "[INIT] ERROR" << std::endl;
    }

    std::cout << "[INIT] Galaxie exit" << std::endl;

    return 0;
}
