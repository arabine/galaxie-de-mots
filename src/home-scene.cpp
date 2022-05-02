#include "home-scene.h"
#include "scenes.h"

HomeScene::HomeScene(GfxSystem &s)
    : Scene(s)
{
    mTileMotus = std::make_shared<Image>(GetSystem(), "icons/activity_motus.svg", true);
    mTileMotus->SetVisible(true);
    mTileMotus->SetSvgScale(1.0);
    mTileMotus->SetPos(10, 250);
    mTileMotus->SetActive(true);
    mTileMotus->HandleOnClick([this](){
        SwitchToScene(SCENE_MOTUS);
    });

    AddEntity(mTileMotus);

    mTileTopping = std::make_shared<Image>(GetSystem(), "icons/activity_topping.svg", true);
    mTileTopping->SetVisible(true);
    mTileTopping->SetSvgScale(1.0);
    mTileTopping->SetPos(400, 250);
    AddEntity(mTileTopping);
}

void HomeScene::Draw(SDL_Renderer *renderer)
{
    Scene::Draw(renderer);

    DrawWelcomeWindow();
}


void HomeScene::DrawWelcomeWindow()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowBgAlpha(1.0f); // Transparent background
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    //        ImGui::SetWindowFontScale(2.0);
    ImGui::SetNextWindowSize(ImVec2(GetSystem().GetScreenW() - 20, GetSystem().H(150)));

    ImGui::GetStyle().FrameBorderSize = 2;
    if (ImGui::Begin("Info", NULL, window_flags))
    {
        ImGui::TextWrapped("Bienvenue sur Galaxie De Mots. Vous trouverez ici un ensemble de jeux classiques pour vous entraîner.");
        ImGui::TextWrapped("Ce jeu est  est un Logiciel Libre ; il est gratuit et sans publicité.");
        ImGui::TextWrapped("Le code source est disponible ici : https://github.com/arabine/galaxie-de-mots");
        ImGui::TextWrapped("Contactez moi pour partagez vos idées de jeux à ajouter.");

    }
    ImGui::End();
}
