#include <iostream>
#include "program.h"
#include <SDL2/SDL.h>

const int WIDTH = 800;
const int HEIGHT = 600;

#undef main

int main(int argc, char const *argv[])
{

    program p;
    if (!p.init())
    {
        std::cout << "program not initialised" << std::endl;
        return -1;
    }

    p.run();

    return 0;
}