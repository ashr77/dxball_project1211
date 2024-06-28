#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Ball.h"
#include "Bar.h"
#include "program.h"
#include "Brick.h"
#include "Collision.h"

class Game
{
public:
    Game();
    ~Game();

    Ball mBall;
    Bar mBar;
    Brick mBrick;
    bool mIsrunning;
    int mLives;

    program gameProgram;

    bool init(program *gameProgram);
    void run();
    void cleanup();
    void handleEvents();
    void resetGameState();
    void showGameOverMessage();

    bool gotoMenu = false;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
};
