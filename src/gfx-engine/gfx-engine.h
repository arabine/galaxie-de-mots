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

typedef std::variant<std::string, double, std::int64_t, std::int32_t> Value;

class GfxSystem
{
public:
    Rect GetWindowSize();

protected:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
};


class Group
{
public:
    Group(GfxSystem &s)
        : mSystem(s)
    {
        mEntityIds = 0;

        mOrigin.x = 0;
        mOrigin.y = 0;
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

    // The below functions can be overridden as necessary in our scenes.
    virtual void ProcessEvent(const SDL_Event &event)
    {
        for (auto & e : mEntities)
        {
            e->ProcessEvent(event, mOrigin);
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
            e->Draw(renderer, mOrigin.x, mOrigin.y);
        }
    };

    uint32_t AddEntity(std::shared_ptr<Entity> entity) {
        uint32_t id = mEntityIds;
        entity->SetId(id);
        mEntities.push_back(entity);
        mEntityIds++;
        return id;
    }

    void DeleteEntity(uint32_t id) {
        mEntities.remove_if([id](const std::shared_ptr<Entity> &e){ return e->GetId() == id; });
    }

    // Sort according to Z value of each entity
    void Sort() {
        mEntities.sort([](const std::shared_ptr<Entity> &a, const std::shared_ptr<Entity> &b) {
            return a->GetZ() < b->GetZ();
        });
    }

    void SetOrigin(int x, int y)
    {
        mOrigin.x = x;
        mOrigin.y = y;
    }

    GfxSystem &GetSystem() { return mSystem; }

private:
    GfxSystem &mSystem;
    uint32_t mEntityIds = 0;
    Vector2 mOrigin;
    std::list<std::shared_ptr<Entity>> mEntities;
};


class Scene : public Group
{
public:

    Scene(GfxSystem &s)
        : Group(s)
    {
        uint32_t mGroupIds = 0;
    }

    // Called when scene initially created. Called once.
    virtual void OnCreate(SDL_Renderer *renderer) {
        Group::OnCreate(renderer);

        for (auto & g : mGroups)
        {
            g->OnCreate(renderer);
        }
    }
    // Called when scene destroyed. Called at most once (if a scene
    // is not removed from the game, this will never be called).
    virtual void OnDestroy() {
        Group::OnDestroy();

        for (auto & g : mGroups)
        {
            g->OnDestroy();
        }
    }

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
        Group::ProcessEvent(event);

        for (auto & g : mGroups)
        {
            g->ProcessEvent(event);
        }
    };

    virtual void Draw(SDL_Renderer *renderer)
    {
        Group::Draw(renderer);

        for (auto & g : mGroups)
        {
            g->Draw(renderer);
        }
    };

    virtual void OnMessage(const std::map<std::string, Value> &message){
        (void) message;
    }

    void SwitchToScene(uint32_t newScene, const std::map<std::string, Value> &args = std::map<std::string, Value>()) {
        mSwitchToScene = newScene;
        mArgs = args;
    }

    uint32_t AddGroup(std::shared_ptr<Group> group) {
        uint32_t id = mGroupIds;
        mGroups.push_back(group);
        mGroupIds++;
        return id;
    }

    uint32_t GetNextScene() {
        return mSwitchToScene;
    }

    std::map<std::string, Value> GetArgs()
    {
        return mArgs;
    }

private:
    std::string mName;
    uint32_t mGroupIds;
    uint32_t mSwitchToScene = 0;
    std::map<std::string, Value> mArgs;
    std::vector<std::shared_ptr<Group>> mGroups;
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

    void SetBackgroundColor(const SDL_Color &color) {
        mBackgroundColor = color;
    }

    void AddScene(std::shared_ptr<Scene> scene, uint32_t id);
    void SwitchSceneTo(uint32_t sceneId, const std::map<std::string, Value> &args = std::map<std::string, Value>());

    // Platform independant file loading
    static bool LoadFile(const char *filename, std::string &fileData);
private:
    uint32_t mWidth = 648;
    uint32_t mHeight = 960;

    const uint32_t mMinimumWidth = 648;
    const uint32_t mMinimumHeight = 960;

    SDL_Color mBackgroundColor{14, 23, 29, 255};

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
