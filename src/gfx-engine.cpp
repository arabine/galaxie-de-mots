
#include <algorithm>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <cctype>
#include <chrono>
#include <locale>
#include <codecvt>
#include <array>
#include <thread>
#include <regex>
#include <random>
#include <memory>
#include <filesystem>

// Linux only
#include <sys/stat.h>

#include "gfx-engine.h"
#include "IconsFontAwesome5.h"


ImFont* GfxEngine::mNormalFont = nullptr;
ImFont* GfxEngine::mBigFont = nullptr;


bool GfxEngine::Initialize()
{
    // initiate SDL
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS |
                 SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("[ERROR] %s\n", SDL_GetError());
        return -1;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(
        SDL_WINDOW_OPENGL
        | SDL_WINDOW_RESIZABLE
        | SDL_WINDOW_ALLOW_HIGHDPI
        );
    mWindow = SDL_CreateWindow(
        "Galaxie de mots",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        mWidth,
        mHeight,
        window_flags
        );
    // limit to which minimum size user can resize the window
    SDL_SetWindowMinimumSize(mWindow, mMinimumWidth, mMinimumHeight);

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    size_t font_data_size = 0;
    void* font_data = SDL_LoadFile("fonts/roboto.ttf", &font_data_size);
    mNormalFont = io.Fonts->AddFontFromMemoryTTF(font_data, static_cast<int>(font_data_size), 20.0f);

    // Merge font with normal font
    ImFontConfig config;
    config.MergeMode = true;
//    config.GlyphMinAdvanceX = 20.0f; // Use if you want to make the icon monospaced
//    config.GlyphOffset.y += 1.0;
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

    font_data = SDL_LoadFile("fonts/fa-solid-900.ttf", &font_data_size);
    io.Fonts->AddFontFromMemoryTTF(font_data, static_cast<int>(font_data_size), 16.0f, &config, icon_ranges);

    font_data = SDL_LoadFile("fonts/roboto.ttf", &font_data_size);
    mBigFont = io.Fonts->AddFontFromMemoryTTF(font_data, static_cast<int>(font_data_size), 50);

    io.Fonts->Build();

    io.IniFilename = nullptr; // disable .ini save/load windows sizes and locations

    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark(&style);

    ImVec4* colors = style.Colors;

    style.FrameRounding     = 3.0f;
    style.FrameBorderSize   = 2;
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);

    // Setup renderer    
    mRenderer =  SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED);

    // setup platform/renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(mWindow);
    ImGui_ImplSDLRenderer_Init(mRenderer);

    return mRenderer != nullptr;
}

uint32_t GfxEngine::StartFrame()
{
    SDL_RenderClear(mRenderer);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // without it you won't have keyboard input and other things
        ImGui_ImplSDL2_ProcessEvent(&event);
        // you might also want to check io.WantCaptureMouse and io.WantCaptureKeyboard
        // before processing events

        switch (event.type)
        {
        case SDL_QUIT:
            break;

        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                return 10000;
                // break;
            case SDL_WINDOWEVENT_RESIZED:
                mWidth = event.window.data1;
                mHeight = event.window.data2;
                // std::cout << "[INFO] Window size: "
                //           << windowWidth
                //           << "x"
                //           << windowHeight
                //           << std::endl;
                break;
            }
            break;
        }
    }

    // start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(mWindow);
    ImGui::NewFrame();



    return 0;
}


void GfxEngine::EndFrame()
{
    // rendering
    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(mRenderer);
}

void GfxEngine::Close()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();  

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

