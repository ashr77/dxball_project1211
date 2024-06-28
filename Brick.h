#pragma once

#include <SDL2/SDL.h>

class Brick
{
public:
    SDL_Rect BrickRect;

    Brick();
    ~Brick();

    Brick(int x, int y);

    int X;
    int Y;
    bool isVisible;
    bool destroyed;
    static const int Length = 50;
    static const int Width = 20;
    static const int buffer = 2;
    static const int NUM_BricksHorizontal = 30;
    static const int NUM_BricksVertical = 10;
    SDL_Rect BrickArray[NUM_BricksVertical][NUM_BricksHorizontal];
    bool isAlive[NUM_BricksVertical][NUM_BricksHorizontal];

    int getx()
    {
        return X;
    }

    int gety()
    {
        return Y;
    }

    void handleBrickEvent(SDL_Event &event);
    void brickRender(SDL_Renderer *renderer);
    void CreateBrickArray();

};