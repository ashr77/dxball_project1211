#pragma once

#include <SDL2/SDL.h>

class Bar
{
public:

    Bar();
    ~Bar();

    Bar(int x, int y);

    int X;
    int Y;
    int Length = 50;
    int Width = 10;

    int getx()
    {
        return X;
    }
    int gety()
    {
        return Y;
    }

    void handleBarEvent(SDL_Event &event);
    void barRender(SDL_Renderer *renderer);

    SDL_Rect barRect;
};