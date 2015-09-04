#include "OpenGLBuffer.h"

OpenGLBuffer::OpenGLBuffer(GLenum target): target(target), bound(false), usage(GL_NONE), elemSize(0), elemCount(0) {
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

void OpenGLBuffer::release() {
    if (bound) {
        glBindBuffer(target, 0);
        bound = false;
    }
}

void OpenGLBuffer::setData(size_t elemSize, size_t count, const void *data, GLenum usage) {
    bind();
    this->usage = usage;
    this->elemCount = count;
    this->elemSize = elemSize;
    glBufferData(target, elemSize * count, data, usage);
}

void OpenGLBuffer::clear() {
    setData(0, 0, nullptr, usage);
    release();
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
    //glVertexAttribPointer(vPos, size, type, static_cast<GLboolean>(normalized), size * elemSize, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);
}

size_t OpenGLBuffer::count() {
    return elemCount;
}