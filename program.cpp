#include <SDL2/SDL.h>
#include <iostream>
#include "program.h"
#include "Menu.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const char *TITLE = "Game";
const int xpos = SDL_WINDOWPOS_CENTERED;
const int ypos = SDL_WINDOWPOS_CENTERED;

void program()
{
    SDL_Window *Mwindow;
    SDL_Renderer *Mrenderer;
}

bool program::init()
{
    int flags = 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised..." << std::endl;

        Mwindow = SDL_CreateWindow("Game", xpos, ypos, WIDTH, HEIGHT, flags);
        if (Mwindow)
        {
            std::cout << "Window created!" << std::endl;
        }

        Mrenderer = SDL_CreateRenderer(Mwindow, -1, 0);
        if (Mrenderer)
        {
            // SDL_SetRenderDrawColor(Mrenderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        // Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return false;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        Mix_Music *bgMusic = Mix_LoadMUS("duck_music.mp3");
        if (!bgMusic)
        {
            std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        if (Mix_PlayMusic(bgMusic, -1) == -1)
        {
            std::cerr << "Failed to play background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }

        isRunningMenu = true;
        isRunningGame = false;
        return true;
    }

    return false;
}

void program::run()
{
    showSplashScreen();

    Menu menu;
    menu.init(this);

    while (menu.isRunning)
    {
        menu.run();
    }
}

void program::showSplashScreen()
{
    // Load the splash image
    SDL_Surface *splashSurface = IMG_Load("Images/intro.png");
    if (splashSurface == nullptr)
    {
        std::cerr << "Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture *splashTexture = SDL_CreateTextureFromSurface(Mrenderer, splashSurface);
    SDL_FreeSurface(splashSurface);

    if (splashTexture == nullptr)
    {
        std::cerr << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Render the splash image
    SDL_RenderClear(Mrenderer);
    SDL_RenderCopy(Mrenderer, splashTexture, NULL, NULL);
    SDL_RenderPresent(Mrenderer);

    // Delay to show the splash screen
    SDL_Delay(3000); // Show splash screen for 3 seconds

    // Cleanup
    SDL_DestroyTexture(splashTexture);
    SDL_RenderClear(Mrenderer);
}