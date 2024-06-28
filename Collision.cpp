#include "Collision.h"
#include <SDL2/SDL.h>
#include "Brick.h"
#include <iostream>

bool Collision::checkRectCollision(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y)
    {
        return true;
    }

    return false;
}
bool Collision::checkCollision(Ball &ball, Bar bar, Brick &bricks)
{
    // // Ball collision with wall
    // if (ball.X < wall_X1 || ball.X + ball.radius * 2 > wall_X2)
    // {
    //    ball.velocityX *= -1; // Reverse x-velocity
    // }

    // if (ball.Y < wall_Y1 || ball.Y + ball.radius * 2 > wall_Y2)
    // {
    //    ball.velocityY *= -1; // Reverse y-velocity
    // }
    // Ball collision with left and right walls
    if (ball.X < 0 || ball.X + ball.radius * 2 > 800)
    {
        ball.velocityX *= -1; // Reverse x-velocity
    }

    // Ball collision with top wall
    if (ball.Y < 0)
    {
        ball.velocityY *= -1; // Reverse y-velocity
    }

    // // Ball collision with bar
    if (checkRectCollision(ball.BallRect, bar.barRect))
    {
        ball.velocityY *= -1; // Reverse y-velocity
    }

    // Ball collision with bricks
    for (int i = 0; i < bricks.NUM_BricksVertical; i++)
    {
        for (int j = 0; j < bricks.NUM_BricksHorizontal; j++)
        {
            if (bricks.isAlive[i][j] == true)
            {
                if (checkRectCollision(ball.BallRect, bricks.BrickArray[i][j]))
                {
                    ball.velocityY *= -1;
                    bricks.isAlive[i][j] = false;
                    //std::cout << "Collision with brick" << std::endl;
                }
            }
        }
    }

    // Update the position of the ball
    ball.X += ball.velocityX;
    ball.Y += ball.velocityY;

    return false; // Assuming there's no game-over condition in this function
}