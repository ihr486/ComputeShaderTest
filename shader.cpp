#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ComputeShader::ComputeShader(const char *filename)
{
    m_program = glCreateProgram();
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    std::ifstream source_file(filename);
    std::ostringstream source_stream;
    source_stream << source_file.rdbuf();
    std::string source_string = source_stream.str();
    std::cout << source_string << std::endl;
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
    std::cerr << filename << " loaded." << std::endl;
}

void ComputeShader::use()
{
    glUseProgram(m_program);
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

Shader::Shader(const char *vertex_path, const char *fragment_path)
{
    m_program = glCreateProgram();
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    std::ifstream vertex_file(vertex_path);
    std::ostringstream vertex_stream;
    vertex_stream << vertex_file.rdbuf();
    std::string vertex_string = vertex_stream.str();
    std::cout << vertex_string << std::endl;
    const GLchar *vertex_list[] = {vertex_string.c_str()};
    glShaderSource(vertex_shader, 1, vertex_list, NULL);
    glCompileShader(vertex_shader);
    GLint result;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        GLint length;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetShaderInfoLog(vertex_shader, length, NULL, log.data());
        log[length] = '\0';
        std::cerr << "Error while compiling vertex shader:" << log.data() << std::endl;
    }
    glAttachShader(m_program, vertex_shader);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::ifstream fragment_file(fragment_path);
    std::ostringstream fragment_stream;
    fragment_stream << fragment_file.rdbuf();
    std::string fragment_string = fragment_stream.str();
    std::cout << fragment_string << std::endl;
    const GLchar *fragment_list[] = {fragment_string.c_str()};
    glShaderSource(fragment_shader, 1, fragment_list, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        GLint length;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetShaderInfoLog(fragment_shader, length, NULL, log.data());
        log[length] = '\0';
        std::cerr << "Error while compiling fragment shader:" << log.data() << std::endl;
    }
    glAttachShader(m_program, fragment_shader);
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &result);
    if(!result) {
        GLint length;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetProgramInfoLog(m_program, length, NULL, log.data());
        log[length] = '\0';
        std::cerr << "Error while linking vertex and fragment shaders:" << log.data() << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::use()
{
    glUseProgram(m_program);
}
