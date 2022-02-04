#ifndef GFX_ENGINE_H
#define GFX_ENGINE_H

// SDL
#include <SDL2/SDL.h>

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

struct Vector2f
{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;
};

struct Vector2
{
    Vector2()
        : x(0)
        , y(0)
    {}

    Vector2(int p_x, int p_y)
        : x(p_x)
        , y(p_y)
    {}

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }

    int x, y;
};


struct Rect : Vector2f
{
    int w;
    int h;

    Rect() {
        w = 0;
        h = 0;
    }
};


class GfxSystem
{
public:
    Rect GetWindowSize();

protected:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
};


class Entity
{
public:
    Entity(GfxSystem &s)
        : mSystem(s)
    {
        mRect.x = 0;
        mRect.y = 0;
        mRect.w = 0;
        mRect.h = 0;
    }

    virtual void OnCreate(SDL_Renderer *renderer) { (void) renderer; }

    // Manage user interaction (mouse, keyboard...)
    virtual void ProcessEvent(const SDL_Event &event)
    {
        (void) event;
    }
    
    // Update state
    virtual void Update(double deltaTime) { (void) deltaTime; }

    // Draw to screen
    virtual void Draw(SDL_Renderer *renderer) { (void) renderer; }

    bool IsVisible() const { return mVisible; }
    void SetVisible(bool visible) { mVisible = visible; }

    int GetX() const
    {
        return mRect.x;
    }

    int GetY() const
    {
        return mRect.y;
    }

    const SDL_Rect &GetRect() const
    {
        return mRect;
    }

    void SetSize(int w, int h)
    {
        mRect.w = w;
        mRect.h = h;
    }

    Vector2f &GetScale()
    {
        return mScale;
    }
    float GetAngle() const
    {
        return mAngle;
    }
    void SetPos(int x, int y)
    {
        mRect.x = x;
        mRect.y = y;
    }

    void SetScale(float x, float y)
    {
        mScale.x = x;
        mScale.y = y;
    }
    void SetAngle(float angle)
    {
        mAngle = angle;
    }

    void SetSceneIdOnwer(uint32_t sceneId) {
        mSceneIdOnwer = sceneId;
    }

    void SetId(uint32_t id) {
        mId = id;
    }

    void SetZ(uint32_t z) {
        mZ = z;
    }

    uint32_t GetZ() const { return mZ; }

    GfxSystem &GetSystem() { return mSystem; }

private:
    GfxSystem &mSystem; // keep it first please

    uint32_t mSceneIdOnwer = 0;
    uint32_t mId = 0;
    uint32_t mZ = 0; // pseudo Z value (order of drawing)

    bool mVisible = true;
    SDL_Rect mRect;
 //   Vector2f mPos;
    float mAngle = 0;
    Vector2f mScale = Vector2f(1, 1);
};

class Image : public Entity
{

public:
    Image(GfxSystem &system, const std::string &path);

    ~Image();

    virtual void OnCreate(SDL_Renderer *renderer) override;

    virtual void Draw(SDL_Renderer *renderer) override;

    void DrawEx(SDL_Renderer *renderer, int x, int y);

    void SetHighlight(bool enable) { mHighlight = enable; }

    bool IsHighlighted() const { return mHighlight; }

private:
    std::string mPath;
    SDL_Texture *mTexture = nullptr;

    bool mHighlight = false;
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
    virtual void OnActivate(SDL_Renderer *renderer)
    {
        mSwitchToScene = 0;
        (void) renderer;
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

    uint32_t AddEntity(std::shared_ptr<Entity> entity) {
        uint32_t id = mEntityIds;
        entity->SetId(id);
        mEntities.push_back(entity);
        mEntityIds++;
        return id;
    }

    GfxSystem &GetSystem() { return mSystem; }

    void SwitchToScene(uint32_t newScene) {
        mSwitchToScene = newScene;
    }

    uint32_t GetNextScene() {
        return mSwitchToScene;
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

};



class GfxEngine : public GfxSystem
{
public:
    GfxEngine()
    {

    }

    ~GfxEngine()
    {

    }

    bool Initialize();

    void Warmup();
    uint32_t Process();

    void Close();

    void AddScene(std::shared_ptr<Scene> scene, uint32_t id);
    void SwitchSceneTo(uint32_t sceneId);

    static SDL_Texture *LoadSVG(SDL_Renderer *renderer, const char *filename);
    static SDL_Texture *RenderSVG(SDL_Renderer *renderer, char *data);
    static SDL_Texture *LoadImage(SDL_Renderer *renderer, const char *filename);
    static std::string FileToString(const std::string &filePath);
    static bool FileExists(const std::string &fileName);
private:
    uint32_t mWidth = 1152;
    uint32_t mHeight = 648;

    const uint32_t mMinimumWidth = 1152;
    const uint32_t mMinimumHeight = 648;

    Uint64 currentTick = 0;
    Uint64 lastTick = 0;
    double deltaTime = 0;

    // Key: id
    std::map<uint32_t, std::shared_ptr<Scene>> mScenes;
    bool mSceneActivated = false;
    uint32_t mCurrentSceneId = 0;
};

#endif // GFX_ENGINE_H
