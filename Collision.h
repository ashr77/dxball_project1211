#pragma once

#include <SDL2/SDL.h>
#include "Ball.h"
#include "Bar.h"
#include "Brick.h"

class Collision
{
    int wall_X1 = 0;
    int wall_Y1 = 0;
    int wall_X2 = 800;
    int wall_Y2 = 600;

public:
    bool checkCollision(Ball &ball, Bar bar, Brick &bricks);
    bool checkRectCollision(SDL_Rect a, SDL_Rect b);
};