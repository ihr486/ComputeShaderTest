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
    static GLint get_max_localsize_x();
    static GLint get_max_localsize_y();
    static GLint get_max_localsize_z();
    GLuint get_uniform_location(const char *name);
};

#endif
