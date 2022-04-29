
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <iostream>
#include "motus-gui.h"
#include "home-scene.h"
#include "scenes.h"
#include "application.h"

extern "C" int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    GfxEngine mGfx;
    GfxEngine::Message msg;

    Application app;

    app.GetRandomWord(5);

    if (mGfx.Initialize("Galaxie de mots"))
    {
        std::cout << "[INIT] Success" << std::endl;

        bool loop = true;
        auto motusScene = std::make_shared<MotusGui>(mGfx);
        mGfx.AddScene(motusScene, SCENE_MOTUS);

        auto homeScene = std::make_shared<HomeScene>(mGfx);
        mGfx.AddScene(homeScene, SCENE_HOME);

        mGfx.SwitchSceneTo(SCENE_HOME); // First scene
        mGfx.Warmup();

        motusScene->Initialize();

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
