#include "home-scene.h"
#include "scenes.h"

HomeScene::HomeScene(GfxSystem &s)
    : Scene(s)
{
    mTileMotus = std::make_shared<Image>(GetSystem(), "icons/activity_motus.svg", true);
    mTileMotus->SetVisible(true);
    mTileMotus->SetSvgScale(1.0);
    mTileMotus->SetActive(true);
    mTileMotus->HandleOnClick([this]()
                              { SwitchToScene(SCENE_MOTUS); });

    AddEntity(mTileMotus);

    mTileTopping = std::make_shared<Image>(GetSystem(), "icons/activity_topping.svg", true);
    mTileTopping->SetVisible(true);
    mTileTopping->SetSvgScale(1.0);

    AddEntity(mTileTopping);
}

void HomeScene::Update(double deltaTime)
{
    Scene::Update(deltaTime);

    mTileMotus->SetPos(10, static_cast<int>(mWelcomeSize + 50.0));
    mTileTopping->SetPos(400, static_cast<int>(mWelcomeSize + 50));
}

void HomeScene::Draw(SDL_Renderer *renderer)
{
    Scene::Draw(renderer);

    DrawWelcomeWindow();
}

void HomeScene::OnMessage(MessageQueue &message)
{
    static const std::string dbgKey = "debug";

    for (; !message.empty(); message.pop_front())
    {
        auto m = message.front();

        if (m.first == dbgKey)
        {
            m_debugTxt = std::get<std::string>(m.second);
        }
    }
}

static const char *welcomeText = "Bienvenue sur Galaxie De Mots. Vous trouverez ici un ensemble de jeux de mots classiques pour vous entraîner.\n"
                                 "Ce jeu est un Logiciel Libre : il est gratuit et sans publicité.\n"
                                 "Le code source est disponible ici : https://github.com/arabine/galaxie-de-mots\n"
                                 "Venez proposer des jeux à ajouter!";

void HomeScene::DrawWelcomeWindow()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
                                    ImGuiWindowFlags_AlwaysAutoResize |
                                    ImGuiWindowFlags_NoSavedSettings |
                                    ImGuiWindowFlags_NoFocusOnAppearing |
                                    ImGuiWindowFlags_NoNav |
                                    ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowBgAlpha(1.0f);
    ImGui::SetNextWindowPos(ImVec2(10, 200), ImGuiCond_Always);
    //        ImGui::SetWindowFontScale(2.0);
    ImGui::SetNextWindowSize(ImVec2(GetSystem().GetScreenW() - 20, 0));
    //, GetSystem().H(150)
    ImGui::GetStyle().FrameBorderSize = 2;
    if (ImGui::Begin("Info", NULL, window_flags))
    {
        ImGui::TextWrapped("%s", m_debugTxt.c_str());
        mWelcomeSize = ImGui::GetWindowSize().y;
    }
    ImGui::End();
}
