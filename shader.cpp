#include "shader.h"

GLuint load_compute_shader(const char *filename)
{
    GLuint program = glCreateProgram();
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    std::ifstream source_file(filename);
    std::ostringstream source_stream;
    source_stream << source_file.rdbuf();
    std::string source_string = source_stream.str();
    glShaderSource(compute_shader, 1, source_string.c_str(), NULL);
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
        return 0;
    }
    glAttachShader(program, compute_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(!result) {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length + 1);
        glGetProgramInfoLog(program, length, NULL, log.data());
        log[length] = '\0';
        std::cerr << "Error while linking compute shader into program:" << log.data() << std::endl;
        return 0;
    }
    return program;
}
