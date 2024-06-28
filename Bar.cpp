#include <SDL2/SDL.h>
#include "Bar.h"

Bar::Bar()
{
}

Bar::~Bar()
{
}

Bar::Bar(int x, int y)
{
    this->X = x;
    this->Y = y;

    this->barRect.x = x;
    this->barRect.y = y;

    barRect.w = Length;
    barRect.h = Width;
}

void Bar::handleBarEvent(SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        int mouseX = event.motion.x;
        barRect.x = mouseX;
    }
}

void Bar::barRender(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &barRect);
}