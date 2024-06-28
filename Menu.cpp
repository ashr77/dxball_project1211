#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "Menu.h"
#include "program.h"
#include <iostream>

SDL_Color white = {255, 255, 255, 255};
SDL_Color black = {0, 0, 0, 255};
SDL_Color red = {255, 0, 0, 255};
SDL_Color green = {0, 255, 0, 255};
SDL_Color blue = {0, 0, 255, 255};

void Menu::renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_Rect &rect)
{
    // Create surface from text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if (!textSurface)
    {
        std::cerr << "Unable to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        std::cerr << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    // Get the dimensions of the text
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Free the surface as we no longer need it
    SDL_FreeSurface(textSurface);

    // Center the text in the given rect
    SDL_Rect renderQuad = {rect.x + (rect.w - textWidth) / 2, rect.y + (rect.h - textHeight) / 2, textWidth, textHeight};

    // Render the texture
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

    // Destroy the texture as we no longer need it
    SDL_DestroyTexture(textTexture);
}

void Menu::init(program *game)
{
    Mwindow = game->Mwindow;
    Mrenderer = game->Mrenderer;
    gameProgram = *game;

    std::cout << "Subsystems Initialised..." << std::endl;
    game->isRunningMenu = true;

    TTF_Init();
    // Load the font using a character array for the font path
    const char fontPath[] = "roboto.ttf"; // Update with the actual path to your font file
    TTF_Font *font = TTF_OpenFont(fontPath, 28);
    if (!font)
    {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255}; // White color for the text

    char text[] = "Play";
    playButton.init(text, 200, 200, 100, 50, red, white);
    SDL_SetRenderDrawColor(Mrenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(Mrenderer, &playButton.destR);
    renderText(Mrenderer, font, text, textColor, playButton.destR);

    char text2[] = "Quit";
    quitButton.init(text2, 200, 300, 100, 50, blue, white);
    SDL_SetRenderDrawColor(Mrenderer, 0, 0, 200, 200);
    SDL_RenderFillRect(Mrenderer, &quitButton.destR);
    renderText(Mrenderer, font, text2, textColor, quitButton.destR);

    char text3[] = "Rules";
    InstructionsButton.init(text3, 200, 400, 100, 50, green, white);
    SDL_SetRenderDrawColor(Mrenderer, 200, 210, 200, 200);
    SDL_RenderFillRect(Mrenderer, &InstructionsButton.destR);
    renderText(Mrenderer, font, text3, textColor, InstructionsButton.destR);

    char text4[] = "Credits";
    CreditsButton.init(text4, 200, 500, 100, 50, red, white);
    SDL_SetRenderDrawColor(Mrenderer, 200, 210, 200, 200);
    SDL_RenderFillRect(Mrenderer, &CreditsButton.destR);
    renderText(Mrenderer, font, text4, textColor, CreditsButton.destR);

    isRunning = true;
    isRunningGame = false;

    std::cout << "Menu initialised..." << std::endl;

    // Close the font when done
    TTF_CloseFont(font);
}

void Menu::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (playButton.isClicked())
            {
                std::cout << "Play button clicked" << std::endl;
                Game game;
                game.init(&gameProgram);
                game.run();

                SDL_RenderClear(Mrenderer);
                init(&gameProgram);
                render();
            }
            if (quitButton.isClicked())
            {
                std::cout << "Quit button clicked" << std::endl;
                gameProgram.isRunning = false;
                isRunning = false;
            }
            if (InstructionsButton.isClicked())
            {
                std::cout << "Instructions button clicked" << std::endl;
            }
            if (CreditsButton.isClicked())
            {
                std::cout << "Credits button clicked" << std::endl;
            }
        }
        break;
    default:
        break;
    }
}

void Menu::render()
{
    SDL_RenderPresent(Mrenderer);
}

void Menu::run()
{
    while (isRunning)
    {
        handleEvents();
        render();
    }
}

void Button::init(char *text, int xpos, int ypos, int width, int height, SDL_Color color, SDL_Color hoverColor)
{
    this->text = text;
    this->xpos = xpos;
    this->ypos = ypos;
    this->width = width;
    this->height = height;
    this->color = color;
    this->hoverColor = hoverColor;

    srcR = {0, 0, width, height};
    destR = {xpos, ypos, width, height};
}

bool Button::isHovered()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x > xpos && x < xpos + width && y > ypos && y < ypos + height)
    {
        return true;
    }
    return false;
}

bool Button::isClicked()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x > xpos && x < xpos + width && y > ypos && y < ypos + height)
    {
        return true;
    }
    return false;
}