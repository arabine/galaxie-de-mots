#include "motus-gui.h"
#include "gfx-engine.h"
#include "IconsFontAwesome5.h"
#include <chrono>

#include "letter.h"
#include "letter-tile.h"

MotusGui::MotusGui(GfxSystem &s)
    : Scene(s)
{
    mMotus.Initialize();

    mTextWin = "Youpiii tu as gagné. Une autre partie ?";
    mTextLost = "Hooo mince alors tu as perdu :(\nLe mot était : ";

    auto l = std::make_shared<Letter>(GetSystem(), 'a');
    l->SetVisible(true);
   // card->SetScale(0.75, 0.75);
    AddEntity(l);

    auto t = std::make_shared<LetterTile>(GetSystem());
    t->SetVisible(true);
    t->SetPos(200, 200);
   // card->SetScale(0.75, 0.75);
    AddEntity(t);
}

