#ifndef GFX_ENGINE_H
#define GFX_ENGINE_H

// SDL
#include <SDL.h>

// Dear ImGui
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

// C++
#include <vector>
#include <iostream>
#include <list>
#include <memory>
#include <map>
#include <algorithm>
#include <functional>

class GfxEngine
{
public:
    GfxEngine()
    {

    }

    ~GfxEngine()
    {

    }

    bool Initialize();

    uint32_t StartFrame();
    void EndFrame();

    void Close();
    uint32_t GetWindowWidth() const { return mWidth; }
    uint32_t GetWindowHeight() const { return mHeight; }

    static void PushBigFont() { ImGui::PushFont(mBigFont); }
    static void PopBigFont() { ImGui::PopFont(); }


private:
    uint32_t mWidth = 648;
    uint32_t mHeight = 960;

    const uint32_t mMinimumWidth = 648;
    const uint32_t mMinimumHeight = 960;

    static ImFont* mNormalFont;
    static ImFont* mBigFont;

    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
};

#endif // GFX_ENGINE_H
