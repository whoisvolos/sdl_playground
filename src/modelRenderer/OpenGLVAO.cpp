#include "OpenGLVAO.h"

OpenGLVAO::OpenGLVAO() {
    glGenVertexArrays(1, &vao);
}

OpenGLVAO::~OpenGLVAO() {
    unbind();
    glDeleteVertexArrays(1, &vao);
}

void OpenGLVAO::bind() {
    glBindVertexArray(vao);
}

void OpenGLVAO::unbind() {
    glBindVertexArray(0);
}