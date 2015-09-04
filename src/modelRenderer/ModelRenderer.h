#pragma once

#include "../AppContainer.h"
#include "../logger.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLVAO.h"
#include "OpenGLBuffer.h"
#include <SDL.h>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <tiny_obj_loader.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace tinyobj;

class ModelRenderer : public AppContainer {
private:
    const char*modeFile = nullptr;
    SDL_GLContext glContext = nullptr;

    std::vector<shape_t> shapes;
    std::vector<material_t> materials;

    /*
    OpenGLShaderProgram* program;
    OpenGLVAO* vao;
    OpenGLBuffer* vertices;
    OpenGLBuffer* indices;
    */

    glm::mat4 worldMatrix;
    glm::mat4 cameraMatrix;
    glm::mat4 projectionMatrix;

    GLchar* vertexSource;
    GLchar*fragmentSource;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint vao;
    GLuint vbo;

public:
    virtual void onEvent(SDL_Event& event) override;
    virtual void onTick(float update) override;
    virtual void onRender() override;
    virtual int afterInit() override;

    ModelRenderer(const char* name, const char* modelFile);
    ~ModelRenderer();

    void logProgramParams() const;
};
