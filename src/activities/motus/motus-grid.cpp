 
#include "motus-grid.h"



static const double TILE_SIZE = 0.8;

MotusGrid::MotusGrid(GfxSystem &s, Motus &motus)
    : Group(s)
    , mMotus(motus)
{
    SetOrigin(100, 200);

    mEmptyTile = std::make_shared<Letter>(GetSystem(), "letters/empty_tile.svg", TILE_SIZE, [] {});
    mEmptyTile->SetActive(false);
    mEmptyTile->SetVisible(true);
    AddEntity(mEmptyTile);

    int x = 0;
    int y = 0;
    for (int i = 0; i < mMotus.GetNbLines(); i++)
    {
        for (int j = 0; j < mMotus.GetNbLetters(); j++)
        {
            mClones.push_back(Vector2(x, y, true));
            x += 90;
        }
        y += 90;
        x = 0;
    }

    Initialize();
}

void MotusGrid::Initialize()
{
    for (int i = 0; i < mClones.size(); i++)
    {
        mClones[i].enable = true;
    }
    mEmptyTile->SetClones(mClones);

    for (const auto &c : mGrid)
    {
        DeleteEntity(c->GetId());
    }
    mGrid.clear();
    mLetterPos = 0;
}

void MotusGrid::DeleteLast()
{
    if (mLetterPos > 0)
    {
        mLetterPos--;

        // Display (enable) empty tile at this position
        mClones[mLetterPos].enable = true;
        mEmptyTile->SetClones(mClones);
        uint32_t idToDelete = mGrid.back()->GetId();
        mGrid.pop_back();
        DeleteEntity(idToDelete);
    }
}

void MotusGrid::AppendLetter(char c)
{
    if (mLetterPos < mClones.size())
    {
        // On va maintenant créer une tile de lettre
        auto t = std::make_shared<Letter>(GetSystem(), std::string("letters/letter_") + c + std::string(".svg"), TILE_SIZE, [] {});
        t->SetActive(false);
        t->SetVisible(true);
        t->SetBackgroundOpacity(0.0);
        t->SetPos(mClones[mLetterPos].x, mClones[mLetterPos].y); // on place la tile à la même place que la tile vide
        AddEntity(t);
        mGrid.push_back(t);

        mLetterPos++;
    }
}

void MotusGrid::Validate(const std::string &codage)
{
    if (mGrid.size() >= codage.size())
    {
        int start_idx = mGrid.size() - codage.size();
        int idx = 0;
        for (int i = start_idx; i < (start_idx + codage.size()); i++)
        {
            if (codage[idx] == '0')
            {
                // La lettre n'est pas dans le mot
                mGrid[i]->SetBackgroundColor("#3A3A3C"); // gris
            }
            else if (codage[idx] == '1')
            {
                // Mauvaise place
                mGrid[i]->SetBackgroundColor("#D3952A"); // orange
            }
            else
            {
                // Bonne et bien placée
                mGrid[i]->SetBackgroundColor("#3EAA42"); // vert
            }
            mGrid[i]->SetBackgroundOpacity(1.0);
            mGrid[i]->Rebuild();
            // Disable empty tile
            mClones[i].enable = false;
            mEmptyTile->SetClones(mClones);

            idx++;
        }
    }
    else
    {
        LOG_DEBUG("Internal error");
    }
}
