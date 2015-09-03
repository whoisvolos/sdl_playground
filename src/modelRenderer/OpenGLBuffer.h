#pragma once

#include <GL/glew.h>
#include "OpenGLShaderProgram.h"

class OpenGLBuffer {
protected:
    GLuint vbo;
    GLenum target;
    GLenum usage;
    bool bound;
    size_t size;
    OpenGLBuffer(GLenum usage);

public:
    ~OpenGLBuffer();

    static OpenGLBuffer* arrayBuffer();
    static OpenGLBuffer* indexBuffer();

    void bind();
    void setPointerForProgram(const OpenGLShaderProgram* program, const char *attrName, GLint size, GLenum type, bool normalized = false);
    void unbind();
    void setData(size_t size, const void* data, GLenum usage);
    void clear();
};