#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture
{
    GLuint m_texture;
    GLuint m_vertex_buffer;
public:
    Texture(int width, int height) {
        /*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        GLubyte *pixels = (GLubyte *)malloc(width * height * 4);
        for(int iy = 0; iy < height; iy++) {
            for(int ix = 0; ix < width; ix++) {
                pixels[(iy * width + ix) * 4 + 0] = 255;
                pixels[(iy * width + ix) * 4 + 1] = 255;
                pixels[(iy * width + ix) * 4 + 2] = 255;
                pixels[(iy * width + ix) * 4 + 3] = 255;
            }
        }*/
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //free(pixels);
        const GLfloat vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 0.0f
        };
        glGenBuffers(1, &m_vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    }
    /*Texture(const char *filename) {
        SDL_Surface *surface = SDL_LoadBMP(filename);
        SDL_LockSurface(surface);
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_UnlockSurface(surface);
    }*/
    ~Texture() {
        glDeleteTextures(1, &m_texture);
    }
    void bind() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
    void bind_image(GLuint unit, GLenum access) {
        glBindImageTexture(unit, m_texture, 0, GL_FALSE, 0, access, GL_RGBA8);
    }
    void render() {
        bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLfloat *)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLfloat *)0 + 2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
};

#endif
