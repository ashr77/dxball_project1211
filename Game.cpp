#include "Game.h"
#include "Ball.h"
#include "Bar.h"
#include "Brick.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 600;

Game::Game()
{
    mWindow = nullptr;
    mRenderer = nullptr;
    mIsrunning = false;

    mBall = Ball(5, 50, 490, 1, -1, mRenderer);
    mBar = Bar(50, 500);
    mBrick = Brick(10, 10);
    mLives = 3;
}

Game::~Game()
{
}

bool Game::init(program *gameProgram)
{
    mWindow = gameProgram->Mwindow;
    mRenderer = gameProgram->Mrenderer;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    mIsrunning = true;
    return true;
}

void Game::handleEvents()
{

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            mIsrunning = false;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            mBar.handleBarEvent(event);
        }
    }

    mBall.ballUpdate();

    Collision collision;
    collision.checkCollision(mBall, mBar, mBrick);

    // Check if the ball hit the ground and update lives
    if (mBall.Y + mBall.radius * 2 >= WINDOW_HEIGHT)
    {
        mLives--;
        if (mLives > 0)
        {
            mBall.resetPosition();
        }
        else
        {
            std::cout << "Game Over" << std::endl;
            showGameOverMessage();
            mIsrunning = false;
            gotoMenu = true;
            gameProgram.isRunningGame = false;
            gameProgram.isRunningMenu = true;
        }
    }

    // mBar.handleBarEvent(event);
}

void Game::run()
{
    while (mIsrunning)
    {
        handleEvents();

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        mBall.ballRender(mRenderer);
        mBar.barRender(mRenderer);
        mBrick.brickRender(mRenderer);

        SDL_RenderPresent(mRenderer);
        SDL_Delay(5);
    }
}

void Game::cleanup()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    IMG_Quit();
    SDL_Quit();
}

void Game::showGameOverMessage()
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game Over", "Skill Issue", mWindow);
}