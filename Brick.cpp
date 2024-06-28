#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "program.h"
#include "Brick.h"

Brick::Brick()
{
}

Brick::~Brick()
{
}

Brick::Brick(int x, int y)
{
    this->X = x;
    this->Y = y;

    this->BrickRect.x = X;
    this->BrickRect.y = Y;

    BrickRect.w = Length;
    BrickRect.h = Width;

    isVisible = true;

    CreateBrickArray();
}

void Brick::CreateBrickArray()
{
    for (int i = 0; i < NUM_BricksVertical; i++)
    {
        for (int j = 0; j < NUM_BricksHorizontal; j++)
        {

            SDL_Rect thisBrick;
            thisBrick.h = Width;
            thisBrick.w = Length;
            thisBrick.x = j * Length + j * buffer;
            thisBrick.y = i * Width + i * buffer;

            BrickArray[i][j] = thisBrick;
            isAlive[i][j] = true;
        }
    }
}

void Brick::handleBrickEvent(SDL_Event &event)
{
}

void Brick::brickRender(SDL_Renderer *renderer)
{
    SDL_Surface *imageSurface = IMG_Load("brick_image.png"); // Replace with the actual path to your image
    if (!imageSurface)
    {
        std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!imageTexture)
    {
        std::cerr << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    for (int i = 0; i < NUM_BricksVertical; i++)
    {
        for (int j = 0; j < NUM_BricksHorizontal; j++)
        {
            if (isAlive[i][j] == false)
                continue;

            // Render the texture
            SDL_RenderCopy(renderer, imageTexture, NULL, &BrickArray[i][j]);
        }
    }

    SDL_DestroyTexture(imageTexture); // Destroy texture when no longer needed

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderFillRect(renderer, &BrickRect);
}