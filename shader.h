#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class ComputeShader
{
    GLuint m_program;
public:
    ComputeShader(const char *filename);
    ~ComputeShader();
    void use();
};

#endif
