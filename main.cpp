#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <GL/glew.h>

#include "shader.h"

int main(int argc, const char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("OpenGL ComputeShader test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 360, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(window == nullptr) {
        std::cerr << "Failed to create an SDL window." << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        std::cerr << "Failed to create an SDL renderer." << std::endl;
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    glewExperimental = 1;
    glewInit();

    SDL_Event event;
    do {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) break;
        }
    } while(event.type != SDL_QUIT);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
