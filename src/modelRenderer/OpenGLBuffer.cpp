#include "OpenGLBuffer.h"

OpenGLBuffer::OpenGLBuffer(GLenum target): target(target), bound(false), usage(GL_NONE), size(0) {
    glGenBuffers(1, &vbo);
}

OpenGLBuffer::~OpenGLBuffer() {
    glDeleteBuffers(1, &vbo);
}

void OpenGLBuffer::bind() {
    if (!bound) {
        glBindBuffer(target, vbo);
        bound = true;
    }
}

void OpenGLBuffer::unbind() {
    if (bound) {
        glBindBuffer(target, 0);
        bound = false;
    }
}

void OpenGLBuffer::setData(size_t size, const void *data, GLenum usage) {
    bind();
    this->usage = usage;
    this->size = size;
    glBufferData(target, size, data, usage);
}

void OpenGLBuffer::clear() {
    setData(size, nullptr, usage);
}

OpenGLBuffer* OpenGLBuffer::arrayBuffer() {
    return new OpenGLBuffer(GL_ARRAY_BUFFER);
}

OpenGLBuffer* OpenGLBuffer::indexBuffer() {
    return new OpenGLBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void OpenGLBuffer::setPointerForProgram(const OpenGLShaderProgram* program, const char *attrName, GLint size, GLenum type, bool normalized) {
    bind();
    GLuint vPos = program->getAttribLocation(attrName);
    glEnableVertexAttribArray(vPos);
    glVertexAttribPointer(vPos, size, type, static_cast<GLboolean>(normalized), size * sizeof(GLfloat), 0);
}