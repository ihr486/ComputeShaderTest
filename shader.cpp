#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ComputeShader::ComputeShader(const char *filename)
{
    GLuint m_program = glCreateProgram();
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    std::ifstream source_file(filename);
    std::ostringstream source_stream;
    source_stream << source_file.rdbuf();
    std::string source_string = source_stream.str();
    const GLchar *source_list[] = {source_string.c_str()};
    glShaderSource(compute_shader, 1, source_list, NULL);
    glCompileShader(compute_shader);
    GLint result;
    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        GLint length;
        glGetShaderiv(compute_shader, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetShaderInfoLog(compute_shader, length, NULL, log.data());
        log[length] = '\0';
        std::cerr << "Error while compiling compute shader:" << log.data() << std::endl;
    }
    glAttachShader(m_program, compute_shader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &result);
    if(!result) {
        GLint length;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetProgramInfoLog(m_program, length, NULL, log.data());
        log[length] = '\0';
        std::cerr << "Error while linking compute shader into program:" << log.data() << std::endl;
    }
    glDeleteShader(compute_shader);
}

void ComputeShader::use()
{
    glUseProgram(m_program);
}

ComputeShader::~ComputeShader()
{
    glDeleteProgram(m_program);
}
