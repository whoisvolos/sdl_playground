#pragma once

#include <GL/glew.h>

class OpenGLVAO {
private:
    GLuint vao;

public:
    OpenGLVAO();
    ~OpenGLVAO();

    void bind();
    void unbind();
};