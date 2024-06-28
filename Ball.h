#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ball
{
public:
    Ball();
    ~Ball();

    int radius;
    int X;
    int Y;
    int velocityX;
    int velocityY;

    SDL_Surface *imageSurface;
    SDL_Texture *imageTexture;

    SDL_Rect BallRect;

    Ball(int radius, int X, int Y, int velocityX, int velocityY, SDL_Renderer *renderer);

    void ballUpdate();
    void ballRender(SDL_Renderer *renderer);

    void resetPosition(); // Declare resetPosition method
};