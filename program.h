#pragma once
#include <SDL2/SDL.h>

class program
{
public:
    SDL_Window *Mwindow;
    SDL_Renderer *Mrenderer;

    SDL_Texture *imageTexture;

    bool isRunningMenu;
    bool isRunningGame;
    bool isRunning;

    bool init();
    void run();
    void handleEvents();
    void showSplashScreen();
};