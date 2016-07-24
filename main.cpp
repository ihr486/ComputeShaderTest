#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"

int main(int argc, const char *argv[])
{
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Compute Shader Test", NULL, NULL);
    if(!window) {
        std::cerr << "Failed to create a GLFW window." << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = 1;
    glewInit();

    std::cout << "Vendor:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer:" << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version:" << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shader Language Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

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

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    std::cout << "X = " << ComputeShader::get_max_localsize_x() << std::endl;
    std::cout << "Y = " << ComputeShader::get_max_localsize_y() << std::endl;
    std::cout << "Z = " << ComputeShader::get_max_localsize_z() << std::endl;

    {
        ComputeShader compute_shader("shader.comp");
        Shader shader("shader.vert", "shader.frag");
        //Texture input("opengl_logo.bmp");
        Texture output(512, 512);

        while(!glfwWindowShouldClose(window)) {
            //glClearColor(1, 1, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            compute_shader.use();
            glUniform1i(0, 0);
            //input.bind_image(0, GL_READ_ONLY);
            output.bind_image(0, GL_WRITE_ONLY);
            glDispatchCompute(32, 32, 1);
            glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT);
            shader.use();
            glUniform1i(0, 0);
            output.render();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();

    return 0;
}
