#ifndef GFX_ENGINE_H
#define GFX_ENGINE_H

// SDL
#include <SDL2/SDL.h>

// Dear ImGui
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "imgui_internal.h"

// C++
#include <vector>
#include <iostream>
#include <list>
#include <memory>
#include <map>
#include <algorithm>
#include <functional>
#include <variant>

// Gfx-Engine
#include "entity.h"
#include "image.h"
#include "xlog.h"

class Value
{
public:

private:
    std::variant<std::string, double, std::int64_t> mValue;
};

class GfxSystem
{
public:
    Rect GetWindowSize();

protected:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
};


class Scene
{
public:

    Scene(GfxSystem &s)
        : mSystem(s)
    {
        mEntityIds = 0;
    }

    // Called when scene initially created. Called once.
    virtual void OnCreate(SDL_Renderer *renderer) {
        for (auto & e : mEntities)
        {
            e->OnCreate(renderer);
        }
    }
    // Called when scene destroyed. Called at most once (if a scene 
    // is not removed from the game, this will never be called).
    virtual void OnDestroy() {}
    // Called whenever a scene is transitioned into. Can be 
    // called many times in a typical game cycle.
    virtual void OnActivate(SDL_Renderer *renderer, const std::map<std::string, Value> &args = std::map<std::string, Value>())
    {
        mSwitchToScene = 0;
        (void) renderer;
        mArgs = args;
    }
    // Called whenever a transition out of a scene occurs. 
    // Can be called many times in a typical game cycle.
    virtual void OnDeactivate() {};
    // The below functions can be overridden as necessary in our scenes.
    virtual void ProcessEvent(const SDL_Event &event)
    {
        for (auto & e : mEntities)
        {
            e->ProcessEvent(event);
        }
    };

    virtual void Update(double deltaTime)
    {
        for (auto & e : mEntities)
        {
            e->Update(deltaTime);
        }
    };

    virtual void Draw(SDL_Renderer *renderer)
    {
        for (auto & e : mEntities)
        {
            e->Draw(renderer);
        }
    };

    virtual void OnMessage(const std::map<std::string, Value> &message){
        (void) message;
    }

    uint32_t AddEntity(std::shared_ptr<Entity> entity) {
        uint32_t id = mEntityIds;
        entity->SetId(id);
        mEntities.push_back(entity);
        mEntityIds++;
        return id;
    }

    GfxSystem &GetSystem() { return mSystem; }

    void SwitchToScene(uint32_t newScene, const std::map<std::string, Value> &args = std::map<std::string, Value>()) {
        mSwitchToScene = newScene;
        mArgs = args;
    }

    uint32_t GetNextScene() {
        return mSwitchToScene;
    }

    std::map<std::string, Value> GetArgs()
    {
        return mArgs;
    }

    // Sort according to Z value of each entity
    void Sort() {
        std::sort(mEntities.begin(), mEntities.end(), [](const std::shared_ptr<Entity> &a, const std::shared_ptr<Entity> &b) {
            return a->GetZ() < b->GetZ();
        });
    }

private:
    GfxSystem &mSystem;
    std::string mName;
    std::vector<std::shared_ptr<Entity>> mEntities;
    uint32_t mEntityIds = 0;
    uint32_t mSwitchToScene = 0;
    std::map<std::string, Value> mArgs;
};



class GfxEngine : public GfxSystem
{
public:
    typedef std::map<std::string, Value> Message;

    GfxEngine()
    {

    }

    ~GfxEngine()
    {

    }

    bool Initialize(const std::string &title);

    void Warmup();
    uint32_t Process(const Message &msg);

    void Close();

    void PushBigFont() { ImGui::PushFont(mBigFont); }
    void PopBigFont() { ImGui::PopFont(); }

    void AddScene(std::shared_ptr<Scene> scene, uint32_t id);
    void SwitchSceneTo(uint32_t sceneId, const std::map<std::string, Value> &args = std::map<std::string, Value>());

    // Platform independant file loading
    static bool LoadFile(const char *filename, std::string &fileData);
private:
    uint32_t mWidth = 1152;
    uint32_t mHeight = 648;

    const uint32_t mMinimumWidth = 1152;
    const uint32_t mMinimumHeight = 648;

    Uint64 currentTick = 0;
    Uint64 lastTick = 0;
    double deltaTime = 0;

    ImFont* mNormalFont = nullptr;
    ImFont* mBigFont = nullptr;

    // Key: id
    std::map<uint32_t, std::shared_ptr<Scene>> mScenes;
    bool mSceneActivated = false;
    uint32_t mCurrentSceneId = 0;

    std::map<std::string, Value> mArgs;
};

#endif // GFX_ENGINE_H
