#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "Game.h"
#include "program.h"

class Button
{

public:
    char *text;
    SDL_Color color;
    SDL_Color hoverColor;
    SDL_Rect srcR, destR;
    int xpos, ypos, width, height;

    void init(char *text, int xpos, int ypos, int width, int height, SDL_Color color, SDL_Color hoverColor);
    bool isClicked();
    bool isHovered();
    void render();
    void run();
};
class Menu
{
public:
    Button playButton;
    Button CreditsButton;
    Button quitButton;
    Button InstructionsButton;

    program gameProgram;

    void init(program *game);
    void handleEvents();
    void update();
    void render();
    void clean();
    void run();
    void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_Rect &rect);

    SDL_Renderer *Mrenderer;
    SDL_Window *Mwindow;
    SDL_Texture *texture;
    SDL_Rect srcR, destR;
    TTF_Font *font;
    SDL_Color color;
    const char *title;
    int xpos, ypos, width, height;
    bool fullscreen;
    int counter;

    bool isRunning;
    bool isRunningGame;
};