#pragma once

#include "../AppContainer.h"
#include "../logger.h"
#include <SDL.h>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "OpenGLShaderProgram.h"
#include "CubeGenerator.h"

class ModelRenderer : public AppContainer {
private:
    const char*modeFile = nullptr;
    SDL_GLContext glContext = nullptr;

    glm::mat4 mvMatrix;
    glm::mat4 cameraMatrix;
    glm::mat4 projectionMatrix;
    glm::mat3 normalMatrix;
    glm::vec3 lightPos;
    glm::vec3 frontColor;
    glm::vec3 backColor;

    GLchar* vertexSource;
    GLchar* fragmentSource;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint vao;
    GLuint vbo[2];

    CubeGenerator cg;

public:
    virtual void onEvent(SDL_Event& event) override;
    virtual void onTick(float update) override;
    virtual void onRender() override;
    virtual int afterInit() override;
    virtual void onResize(int newWidth, int newHeight) override;

    ModelRenderer(const char* name, const char* modelFile);
    ~ModelRenderer();

    void logProgramParams() const;
};
