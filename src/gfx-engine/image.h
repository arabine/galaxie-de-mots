#ifndef IMAGE_H
#define IMAGE_H

#include "entity.h"


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
    size_t font_data_size = 0;

    static std::string LoadFile(const char *filename);
    static SDL_Texture *LoadSVG(SDL_Renderer *renderer, const char *filename);
    static SDL_Texture *RenderSVG(SDL_Renderer *renderer, const std::string &svgData, float scale = 1.0);
    static SDL_Texture *LoadImage(SDL_Renderer *renderer, const char *filename);

private:
    std::string mPath;
    SDL_Texture *mTexture = nullptr;

    bool mHighlight = false;
};


#endif // IMAGE_H
