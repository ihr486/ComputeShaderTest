#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <GL/glew.h>

#include "shader.h"
#include "texture.h"

int main(int argc, const char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

    if(GLEW_ARB_compute_shader) {
        std::cerr << "ARB_compute_shader extension supported." << std::endl;
    } else {
        std::cerr << "ARB_compute_shader extension not supported." << std::endl;
        return -1;
    }
    if(GLEW_ARB_shader_image_load_store) {
        std::cerr << "ARB_shader_image_load_store extension supported." << std::endl;
    } else {
        std::cerr << "ARB_shader_image_load_store extension not supported." << std::endl;
        return -1;
    }

    glEnable(GL_TEXTURE_2D);

    std::cout << "X = " << ComputeShader::get_max_localsize_x() << std::endl;
    std::cout << "Y = " << ComputeShader::get_max_localsize_y() << std::endl;
    std::cout << "Z = " << ComputeShader::get_max_localsize_z() << std::endl;

    {
        ComputeShader shader("compute.glsl");
        //Texture input("opengl_logo.bmp");
        Texture output(512, 512);

        SDL_Event event;
        do {
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT) break;
            }
            shader.use();
            //input.bind_image(0, GL_READ_ONLY);
            output.bind_image(0, GL_WRITE_ONLY);
            glDispatchCompute(32, 32, 1);
            glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);
            glUseProgram(0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            output.render();
            SDL_GL_SwapWindow(window);
        } while(event.type != SDL_QUIT);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
