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
    /*std::ifstream source_file(filename);
    std::ostringstream source_stream;
    source_stream << source_file.rdbuf();
    std::string source_string = source_stream.str();
    std::cout << source_string << std::endl;*/
    const GLchar *source_list[] = {
"layout(local_size_x = 8, local_size_y = 8) in;\n"
"uniform writeonly image2D output;\n"
"void main()\n"
"{\n"
"    imageStore(output, ivec2(gl_GlobalInvocationID), vec4(1, 1, 1, 1));\n"
"}\n"};
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
    std::cerr << filename << " loaded." << std::endl;
}

void ComputeShader::use()
{
    glUseProgram(m_program);
    glUniform1i(glGetUniformLocation(m_program, "output"), 0);
}

ComputeShader::~ComputeShader()
{
    glDeleteProgram(m_program);
}

GLint ComputeShader::get_max_localsize_x()
{
    GLint value;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &value);
    return value;
}

GLint ComputeShader::get_max_localsize_y()
{
    GLint value;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &value);
    return value;
}

GLint ComputeShader::get_max_localsize_z()
{
    GLint value;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &value);
    return value;
}

GLuint ComputeShader::get_uniform_location(const char *name)
{
    return glGetUniformLocation(m_program, name);
}
