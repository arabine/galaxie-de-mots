#include "image.h"
#include "xlog.h"
#include "gfx-engine.h"

Image::Image(GfxSystem &system, const std::string &path)
    : Entity(system)
    , mPath(path)
{
}

Image::~Image()
{

}

void Image::OnCreate(SDL_Renderer *renderer)
{
    Entity::OnCreate(renderer);
    SetTexture(LoadImage(renderer, mPath.c_str()));
}


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

/* Load a SVG type image from an SDL datasource */
SDL_Texture *Image::LoadSVG(SDL_Renderer *renderer, const char *filename)
{
    std::string data;
    SDL_Texture * tex = nullptr;

    if (GfxEngine::LoadFile(filename, data))
    {
        tex = Image::RenderSVG(renderer, data.data());
    }

    if (tex == nullptr)
    {
        tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 20, 20);
    }

    return tex;
}

SDL_Texture *Image::RenderSVG(SDL_Renderer *renderer, const std::string &svgData, float scale)
{
    std::string data = svgData; // on est obligé de créer une copie car nsvgParse modifie le code SVG
    struct NSVGimage *image;
    struct NSVGrasterizer *rasterizer;
    SDL_Surface *surface = NULL;

    /* For now just use default units of pixels at 96 DPI */
    image = nsvgParse(data.data(), "px", 96.0f);

    if ( !image ) {
        //IMG_SetError("Couldn't parse SVG image");
        return NULL;
    }

    rasterizer = nsvgCreateRasterizer();
    if ( !rasterizer ) {
       // IMG_SetError("Couldn't create SVG rasterizer");
        nsvgDelete( image );
        return NULL;
    }

    surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   (int)(image->width * scale),
                                   (int)(image->height * scale),
                                   32,
                                   0x000000FF,
                                   0x0000FF00,
                                   0x00FF0000,
                                   0xFF000000);
    if ( !surface ) {
        nsvgDeleteRasterizer( rasterizer );
        nsvgDelete( image );
        return NULL;
    }

    nsvgRasterize(rasterizer, image, 0.0f, 0.0f, scale, (unsigned char *)surface->pixels, surface->w, surface->h, surface->pitch);
    nsvgDeleteRasterizer( rasterizer );
    nsvgDelete( image );

    return SDL_CreateTextureFromSurface(renderer, surface);
}



SDL_Texture *Image::LoadImage(SDL_Renderer *renderer, const char* filename)
{
    // Read data
    int32_t width, height, bytesPerPixel;
    void* data = stbi_load(filename, &width, &height, &bytesPerPixel, 0);

    // Calculate pitch
    int pitch;
    pitch = width * bytesPerPixel;
    pitch = (pitch + 3) & ~3;

    // Setup relevance bitmask
    int32_t Rmask, Gmask, Bmask, Amask;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    Rmask = 0x000000FF;
    Gmask = 0x0000FF00;
    Bmask = 0x00FF0000;
    Amask = (bytesPerPixel == 4) ? 0xFF000000 : 0;
#else
    int s = (bytesPerPixel == 4) ? 0 : 8;
    Rmask = 0xFF000000 >> s;
    Gmask = 0x00FF0000 >> s;
    Bmask = 0x0000FF00 >> s;
    Amask = 0x000000FF >> s;
#endif
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(data, width, height, bytesPerPixel*8, pitch, Rmask, Gmask, Bmask, Amask);
    SDL_Texture* t = nullptr;
    if (surface)
    {
        t = SDL_CreateTextureFromSurface(renderer, surface);
    }
    else
    {
        t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 20, 20);
    }

    STBI_FREE(data);
    SDL_FreeSurface(surface);
    return t;
}

