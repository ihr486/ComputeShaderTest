#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <GL/glew.h>

class Texture
{
    GLuint m_texture;
public:
    Texture(int width, int height) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    Texture(const char *filename) {
        SDL_Surface *surface = SDL_LoadBMP(filename);
        SDL_LockSurface(surface);
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_UnlockSurface(surface);
    }
    ~Texture() {
        glDeleteTextures(1, &m_texture);
    }
    void bind() {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
    void bind_image(GLuint unit, GLenum access) {
        glBindImageTexture(unit, m_texture, 0, GL_FALSE, 0, access, GL_RGBA32F);
    }
    void render() {
        bind();
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();
    }
};

#endif
