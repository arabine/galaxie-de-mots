#include "entity.h"

Entity::Entity(GfxSystem &s)
    : mSystem(s)
{
    mRect.x = 0;
    mRect.y = 0;
    mRect.w = 0;
    mRect.h = 0;
}
