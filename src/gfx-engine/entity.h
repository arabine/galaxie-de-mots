#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <vector>
#include "SDL.h"

class GfxSystem;

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


class Entity
{
public:
    Entity(GfxSystem &s);

    virtual ~Entity();

    virtual void OnCreate(SDL_Renderer *renderer) { (void) renderer; }

    // Manage user interaction (mouse, keyboard...)
    virtual void ProcessEvent(const SDL_Event &event, const Vector2 &origin)
    {
        (void) event;
    }

    // Update state
    virtual void Update(double deltaTime) { (void) deltaTime; }

    // Draw to screen
    void Draw(SDL_Renderer *renderer, int x_offset = 0, int y_offset = 0);

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

    void SetTexture(SDL_Texture *texture)
    {
        // Before anything, delete old texture
        if (mTexture != nullptr)
        {
            SDL_DestroyTexture(mTexture);
            mTexture = nullptr;
        }

        mTexture = texture;
        int w = 0;
        int h = 0;
        // get the width and height of the texture
        if (SDL_QueryTexture(mTexture, NULL, NULL, &w, &h) == 0)
        {
            SetSize(w, h);
        }
    }

    void SetZ(uint32_t z) {
        mZ = z;
    }

    uint32_t GetZ() const { return mZ; }

    GfxSystem &GetSystem() { return mSystem; }

    void SetClones(const std::vector<Vector2> &clones);

private:
    GfxSystem &mSystem; // keep it first please

    SDL_Texture *mTexture = nullptr;

    uint32_t mSceneIdOnwer = 0;
    uint32_t mId = 0;
    uint32_t mZ = 0; // pseudo Z value (order of drawing)

    bool mVisible = true;
    SDL_Rect mRect;
    float mAngle = 0;
    Vector2f mScale = Vector2f(1, 1);

    std::vector<Vector2> mClones;

    void Render(SDL_Renderer *renderer, const SDL_Rect &pos);
};

#endif // ENTITY_H
