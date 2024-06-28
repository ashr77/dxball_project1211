#include "Ball.h"
#include <iostream>
#include <SDL2/SDL_image.h>

Ball::Ball()
{
    radius = 0;    // Default radius
    X = 0;         // Default initial X position
    Y = 0;         // Default initial Y position
    velocityX = 0; // Default initial X velocity
    velocityY = 0; // Default initial Y velocity
}

Ball::~Ball()
{
}

Ball::Ball(int radius, int X, int Y, int velocityX, int velocityY, SDL_Renderer *renderer)
{
    this->radius = radius;
    this->X = X;
    this->Y = Y;
    this->velocityX = velocityX;
    this->velocityY = velocityY;

    BallRect.x = X;
    BallRect.y = Y;
    BallRect.w = radius * 2;
    BallRect.h = radius * 2;
}

void Ball::ballUpdate()
{
    this->X = X + velocityX;
    this->Y = Y + velocityY;

    BallRect.x = X;
    BallRect.y = Y;
}

void Ball::ballRender(SDL_Renderer *renderer)
{

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &BallRect);
}

void Ball::resetPosition()
{
    X = 50;         // Reset X position
    Y = 490;        // Reset Y position
    velocityX = 1;  // Reset X velocity
    velocityY = -1; // Reset Y velocity

    BallRect.x = X;
    BallRect.y = Y;
}