#include "topping-scene.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>

struct Scrabble
{
    char letter;
    int points;
    int quantity; // nombre de pièces dans le sac
};

static const Scrabble scrabble[] = {
{ 'A', 1, 9 },
{ 'B', 3, 2 },
{ 'C', 3, 2 },
{ 'D', 2, 3 },
{ 'E', 1, 15 },
{ 'F', 4, 2 },
{ 'G', 2, 2 },
{ 'H', 4, 2 },
{ 'I', 1, 8 },
{ 'J', 8, 1 },
{ 'K', 10, 1 },
{ 'L', 1, 5 },
{ 'M', 2, 3 },
{ 'N', 1, 6 },
{ 'O', 1, 1 },
{ 'P', 3, 2 },
{ 'Q', 8, 1 },
{ 'R', 1, 6 },
{ 'S', 1, 6 },
{ 'T', 1, 6 },
{ 'U', 1, 6 },
{ 'V', 4, 2 },
{ 'W', 10, 1 },
{ 'X', 10, 1 },
{ 'Y', 10, 1 },
{ 'Z', 10, 1 },
{ '*', 0, 2 } // joker
};

ToppingScene::ToppingScene(GfxSystem &s)
    : Scene(s)

{
    mKeyboard = std::make_shared<Keyboard>(GetSystem(), *this);
    AddGroup(mKeyboard);
}


void ToppingScene::Initialize()
{

}


// -----------  LES CALLBACKS CLAVIER sont redirigés vers le moteur de jeu uniquement
void ToppingScene::KeyPressed(char c)
{

}

void ToppingScene::EnterPressed()
{

}

void ToppingScene::BackspacePressed()
{

}

