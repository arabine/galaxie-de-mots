#ifndef MOTUS_GRID_H
#define MOTUS_GRID_H

#include "motus.h"
#include "gfx-engine.h"
#include "letter.h"
#include "common.h"

class MotusGrid : public Group
{

public:
    MotusGrid(GfxSystem &s, Motus &motus);

    void Initialize();
    void DeleteLast();
    void AppendLetter(char c);
    void Validate(const std::string &codage);

private:
    Motus &mMotus;
    std::shared_ptr<Letter> mEmptyTile;
    std::vector<Vector2> mClones;
    int mLetterPos;
    std::vector<std::shared_ptr<Letter>> mGrid;
};

#endif // MOTUS_GRID_H
