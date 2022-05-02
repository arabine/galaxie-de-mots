
#include "gfx-engine.h"
#include "IconsMaterialDesign.h"
#include "IconsFontAwesome5.h"


void GfxEngine::AddScene(std::shared_ptr<Scene> scene, uint32_t id)
{
    mScenes[id] = scene;
}

void GfxEngine::SwitchSceneTo(uint32_t sceneId, const std::map<std::string, Value> &args)
{
    mCurrentSceneId = sceneId;
    mSceneActivated = true;
    mArgs = args;
}

uint32_t GfxSystem::GetScreenW()
{
    return mScreenWidth;
}
uint32_t GfxSystem::GetScreenH()
{
    return mScreenHeight;
}

bool GfxEngine::Initialize(const std::string &title)
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
        title.c_str(),
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

    int w, h;
    SDL_GetWindowSize(mWindow, &w, &h);

    mScreenWidth = static_cast<uint32_t>(w);
    mScreenHeight = static_cast<uint32_t>(h);
    mRatioW = w / mWidth;
    mRatioH = h / mHeight;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    size_t font_data_size = 0;
    void* font_data = SDL_LoadFile("fonts/roboto.ttf", &font_data_size);
    mNormalFont = io.Fonts->AddFontFromMemoryTTF(font_data, static_cast<int>(font_data_size), 20.0f * mRatioH);

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

    ImVec4* colors = style.Colors;

    style.WindowRounding    = 2.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    style.ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
    style.GrabRounding      = 2.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    style.AntiAliasedLines  = true;
    style.AntiAliasedFill   = true;
    style.WindowRounding    = 2;
    style.ChildRounding     = 2;
    style.ScrollbarSize     = 16;
    style.ScrollbarRounding = 3;
    style.GrabRounding      = 2;
    style.ItemSpacing.x     = 10;
    style.ItemSpacing.y     = 4;
    style.IndentSpacing     = 22;
    style.FramePadding.x    = 6;
    style.FramePadding.y    = 4;
    style.Alpha             = 1.0f;
    style.FrameRounding     = 3.0f;

    colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    //colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
    colors[ImGuiCol_Border]                = ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
    colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    colors[ImGuiCol_FrameBg]               = ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
    colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
    colors[ImGuiCol_FrameBgActive]         = ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
    colors[ImGuiCol_TitleBg]               = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
    colors[ImGuiCol_TitleBgActive]         = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
    colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
    colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
    colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_CheckMark]             = ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
    colors[ImGuiCol_SliderGrab]            = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                = ImVec4(0.71f, 0.78f, 0.69f, 0.40f);
    colors[ImGuiCol_ButtonHovered]         = ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
    colors[ImGuiCol_ButtonActive]          = ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
    colors[ImGuiCol_Header]                = ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
    colors[ImGuiCol_HeaderHovered]         = ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
    colors[ImGuiCol_HeaderActive]          = ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
//     colors[ImGuiCol_Column]                = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
//     colors[ImGuiCol_ColumnHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
//     colors[ImGuiCol_ColumnActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
    colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
    colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
//     colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_NavHighlight]           = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);

    // Setup renderer    
    mRenderer =  SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED);

    // setup platform/renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(mWindow);
    ImGui_ImplSDLRenderer_Init(mRenderer);

    return mRenderer != nullptr;
}

void GfxEngine::Warmup()
{
   currentTick = SDL_GetPerformanceCounter();

   for (auto &s : mScenes)
   {
       s.second->OnCreate(mRenderer);
   }

}


uint32_t GfxEngine::Process(const Message &msg)
{
    uint32_t nextScene = 0;

    SDL_SetRenderDrawColor(mRenderer, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
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
                break;
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

        if (mScenes.count(mCurrentSceneId))
        {
            auto s = mScenes.at(mCurrentSceneId);
            s->ProcessEvent(event);
        }
    }

    // start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(mWindow);
    ImGui::NewFrame();

    if (mScenes.count(mCurrentSceneId))
    {
        auto s = mScenes.at(mCurrentSceneId);
        if (mSceneActivated)
        {
            mSceneActivated = false;
            s->OnActivate(mRenderer, mArgs);
        }

        lastTick = currentTick;
        currentTick = SDL_GetPerformanceCounter();
        deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

        if (msg.size() > 0)
        {
            s->OnMessage(msg);
        }

        s->Update(deltaTime);
        s->Draw(mRenderer);

        nextScene = s->GetNextScene();
        if (nextScene > 0)
        {
            SwitchSceneTo(nextScene, s->GetArgs());
        }
    }
    else
    {
        // FIXME: log error
    }

    // rendering
    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(mRenderer);

    return nextScene;
}


bool GfxEngine::LoadFile(const char *filename, std::string &fileData)
{
    size_t size = 0;
    bool success = false;
    void* f = SDL_LoadFile(filename, &size);

    if ((f != nullptr) && (size > 0))
    {
        fileData.assign(reinterpret_cast<char *>(f), size);
        success = true;
    }
    return success;
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



