
#include "gfx-engine.h"

#include <iostream>


std::string rawSquare = R"("
<svg width="440" height="440">
  <path d="M100,100 h200 a20,20 0 0 1 20,20 v200 a20,20 0 0 1 -20,20 h-200 a20,20 0 0 1 -20,-20 v-200 a20,20 0 0 1 20,-20 z" fill="green" stroke="grey" stroke-width="3" />
</svg>
")";

class Square : public Entity
{
public:
    Square(GfxSystem &s)
        : Entity(s)
    {

    }
    virtual void OnCreate(SDL_Renderer *renderer) override {
//        std::string newCarColor = replaceStringAll(mDeuxCvSVG, "{{COLOR}}", "#a17321");

        mTexture = GfxEngine::RenderSVG(renderer, rawSquare.data());
        int w = 0;
        int h = 0;
        // get the width and height of the texture
        if (SDL_QueryTexture(mTexture, NULL, NULL, &w, &h) == 0)
        {
            SetSize(w, h);
        }
    }

    virtual void Draw(SDL_Renderer *renderer) override
    {
        SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(mTexture, 255, 255, 255);
        SDL_RenderCopyEx(renderer, mTexture, NULL, &GetRect(), GetAngle(), NULL, SDL_FLIP_NONE);
    }

private:
    std::string mDeuxCvSVG;
    SDL_Texture *mTexture = nullptr;
};


class Word
{
public:
    Word(GfxSystem &g, Scene &s)
        : mGfx(g)
        , mScene(s)
    {

    }

    void Initialize(int letters)
    {
        for (int i = 0; i < letters; i++)
        {
            auto l = std::make_shared<Square>(mGfx);
//            l->SetScale(.5, .5);
            mScene.AddEntity(l);
            mWord.push_back(l);
        }

    }

    void SetPos(int yPos) {
        int x = 50;
        for (auto &square : mWord)
        {
            square->SetPos(50 + x, yPos);
            x += 100;
        }
    }

private:
    GfxSystem &mGfx;
    Scene &mScene;

    std::vector<std::shared_ptr<Square>> mWord;
};



class GridScene : public Scene
{
public:
    GridScene(GfxSystem &g)
     : Scene(g)
    {
        for (int i = 0; i < mTries; i++)
        {
            Word w(GetSystem(), *this);
            w.Initialize(mLetters);
            mGrid.push_back(w);
        }
    }


    virtual void OnCreate(SDL_Renderer *renderer) override {
        Scene::OnCreate(renderer);
    }

    virtual void OnActivate(SDL_Renderer *renderer) override {
        Scene::OnActivate(renderer);
    }

    virtual void Update(double deltaTime) override{
        // Affichage de la grille
        int index = 0;
        for (auto & word : mGrid)
        {
            word.SetPos(50 + index);
            index += 100;
        }

        Scene::Update(deltaTime);
    }

    virtual void Draw(SDL_Renderer *renderer) override{
        Scene::Draw(renderer);
    }

    virtual void ProcessEvent(const SDL_Event &event) override{
         Scene::ProcessEvent(event);
    }

private:
    int mLetters = 5;
    int mTries = 6;


    std::vector<Word> mGrid;
};


extern "C" int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    GfxEngine mGfx;

    mGfx.AddScene(std::make_shared<GridScene>(mGfx), 10);
    mGfx.SwitchSceneTo(10); // First scene

    if (mGfx.Initialize())
    {
        std::cout << "[INIT] Success" << std::endl;

        mGfx.Warmup();
        bool loop = true;

        while (loop)
        {
            // 3. On traite les entrées (clavier/souris) et on affiche le jeu
            if (mGfx.Process() == 10000)
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
